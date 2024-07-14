/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:50:47 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/12 23:56:57 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	export_list(t_list *env)
{
	char	*content;
	char	*var;
	char	*value;
	int		index;

	while (env)
	{
		content = (char *)env->content;
		if ((content[0] != '?' && content[0] != '_') || content[1] == '_')
		{
			index = ft_strchr(content, '=') - content;
			var = ft_substr(content, 0, index);
			value = ft_substr(content, index + 1, ft_strlen(content) - index);
			if (ft_strchr(content, '='))
				printf("declare -x %s=\"%s\"\n", var, value);
			else
				printf("declare -x %s\n", var);
			ft_free(&value);
			ft_free(&var);
		}
		env = env->next;
	}
}

static int	check_var(const char *str)
{
	int	i;

	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_'
			&& !(str[i] == '+' && str[i + 1] == '='))
			return (0);
		i++;
	}
	return (1);
}

void	add_arg_to_env(char *argv, t_env *env)
{
	char	*var;
	char	*value;
	char	*trimmed;
	char	*equals;

	equals = ft_strchr(argv, '=');
	var = NULL;
	value = NULL;
	if (equals)
	{
		var = ft_substr(argv, 0, equals - argv);
		value = ft_strdup(equals + 1);
	}
	else
		var = ft_strdup(argv);
	trimmed = ft_strtrim(var, "+");
	set_env_var(env, "_", trimmed);
	if (equals && *(equals - 1) == '+')
		append_env_var(env, trimmed, value);
	else if (equals)
		set_env_var(env, trimmed, value);
	else if (!is_var_in_env(env, argv))
		ft_lstadd_back(&(env->env), ft_lstnew(ft_strdup(argv)));
	(free(trimmed), free(var), free(value));
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
