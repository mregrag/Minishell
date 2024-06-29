/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:50:47 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/29 20:47:34 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void	export_list(t_node *node)
{
	t_list	*env;
	char	*content;

	env = node->env;
	while (env)
	{
		content = (char *)env->content;
		if (content[0] != '_' || content[0] != '?')
		{
			printf("declare -x %s\"", content);
			printf("\n");

		}
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

int find_char_index(const char *str, char c)
{
	int index = 0;

	if (!str)
		return -1;

	while (str[index] != '\0')
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

void	add_arg_to_env(char *argv, t_node *node)
{
	int	index;
	char	*value;
	char	*var;

	index = find_char_index(argv, '=');
	var = ft_strtrim(ft_substr(argv, 0, index), "+");
	value = ft_substr(argv, index + 1, ft_strlen(argv) - index);
	if (ft_issamechar(value, '$'))
		value = ft_itoa(getpid());
	if (ft_getenv(var, node->env) && !ft_strchr(argv, '+'))
		update_env_var(var, value, node);
	else if (ft_getenv(var, node->env) && argv[index - 1] == '+')
		update_env_var(var, ft_strjoin(ft_getenv(var, node->env), value), node);
	else if (ft_strchr(argv, '='))
		create_env_var(var, value, node);
}

int	ft_export(t_node *node)
{
	int		i;
	char	**argv;

	i = 0;
	argv = node->cmd;
	if (!argv[1])
		return (export_list(node), 0);
	while (*(++argv))
	{
		if (!check_var(*argv))
		{
			print_error("minish","export", *argv, "not a valid identifier");
			update_env_var("?", "1", node);
		}
		else
			add_arg_to_env(*argv, node);
	}
	return (0);
}
