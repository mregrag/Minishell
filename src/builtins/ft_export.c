/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:50:47 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/08 20:03:35 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void	export_list(t_list *env)
{
	char	*content;

	while (env)
	{
		content = (char *)env->content;
		if (content[0] != '?' && content[0] != '_')
			printf("declare -x %s\"\n", content);
		env = env->next;
	}
}

static int	check_var(const char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	find_char_index(const char *str, char c)
{
	int	index;

	index = 0;
	if (!str)
		return (-1);
	while (str[index] != '\0')
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

static void	handle_existing_var(t_env *env, char *var, char *value, int append)
{
	char	*existing_value;
	char	*new_value;

	existing_value = get_env_var(env, var);
	if (existing_value && !append)
	{
		if (value)
			set_env_var(env, var, value);
		else
			set_env_var(env, var, "");
	}
	else if (existing_value && append)
	{
		if (value)
			new_value = ft_strjoin(existing_value, value);
		else
			new_value = ft_strdup(existing_value);
		set_env_var(env, var, new_value);
		free(new_value);
	}
	else if (value)
		set_env_var(env, var, value);
	else
		set_env_var(env, var, "");
	free(existing_value);
}

void	add_arg_to_env(char *argv, t_env *env)
{
	int		index;
	char	*var;
	char	*trimmed_var;
	char	*value;
	int		append;

	index = find_char_index(argv, '=');
	var = ft_substr(argv, 0, index);
	trimmed_var = ft_strtrim(var, "+");
	free(var);
	if (index != -1)
		value = ft_substr(argv, index + 1, ft_strlen(argv) - index);
	else
		value = NULL;
	if (value && ft_issamechar(value, '$'))
	{
		free(value);
		value = ft_itoa(getpid());
	}
	append = 0;
	if (index > 0 && argv[index - 1] == '+')
		append = 1;
	handle_existing_var(env, trimmed_var, value, append);
	(free(trimmed_var), free(value));
}

int	ft_export(t_node *node, t_env *env)
{
	char	**argv;
	t_list	*envp;

	envp = env->env;
	argv = node->cmd;
	if (!argv[1])
		return (export_list(envp), 1);
	argv++;
	while (*argv)
	{
		if (!check_var(*argv))
		{
			print_error("minish", "export", *argv, "not a valid identifier");
			set_env_var(env, "?", "1");
		}
		else
			add_arg_to_env(*argv, env);
		argv++;
	}
	return (1);
}
