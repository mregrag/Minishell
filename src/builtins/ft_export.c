/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:50:47 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/11 19:11:41 by mkoualil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void	export_list(t_list *env)
{
	char	*content;

	while (env)
	{
		content = (char *)env->content;
		if ((content[0] != '?' && content[0] != '_') || content[1] == '_')
			printf("declare -x %s\"\n", content);
		env = env->next;
	}
}

static int	check_var(const char *str)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	if (!ft_isalpha(*str) && *str != '_')
		return (0);

	while (str[i] && str[i] != '=')
	{
		if (str[i] == '-')
			return 0;
		if (str[i] == '+')
			count++;
		if ((!ft_isalnum(str[i]) || str[i] == '_' ) && count > 1)
			return (0);
		i++;
	}
	return (1);
}

void	add_arg_to_env(char *argv, t_env *env)
{
	int		index;
	char	*value;
	char	*var;
	char	*trimmed;
	char	*temp;

	index = ft_strchr(argv, '=') - argv;
	var = ft_substr(argv, 0, index);
	trimmed = ft_strtrim(var, "+");
	set_env_var(env, "_", trimmed);
	free(var);
	value = ft_substr(argv, index + 1, ft_strlen(argv) - index);
	if (get_env_var(env, trimmed) && !ft_strchr(argv, '+'))
		set_env_var(env, trimmed, value);
	else if (get_env_var(env, trimmed) && argv[index - 1] == '+')
	{
		temp = ft_strjoin(get_env_var(env, trimmed), value);
		set_env_var(env, trimmed, temp);
		free(temp);
	}
	else if (ft_strchr(argv, '='))
		set_env_var(env, trimmed, value);
	(free(trimmed), free(value));
}

int	ft_export(t_node *node, t_env *env)
{
	char	**argv;
	t_list	*envp;

	envp = env->env;
	argv = node->cmd;
	if (!argv[1])
		return (export_list(envp), 1);
	while (*(++argv))
	{
		if (!check_var(*argv))
		{
			print_error("minish", "export", *argv, "not a valid identifier");
			set_env_var(env, "?", "1");
		}
		else
			add_arg_to_env(*argv, env);
	}
	return (1);
}
