/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:50:47 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/25 16:11:12 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void	export_list(void)
{
	t_list	*env;

	env = g_minish.env;
	while (env)
	{
		printf("declare -x %s\"", (char *)env->content);
		printf("\n");
		env = env->next;
	}
}

static int	check_var(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	return (1);
}

void	add_arg_to_env(char *argv)
{
	int	index;
	char	*value;
	char	*var;

	index = (int)(ft_strchr(argv, '=') - argv);
	var = ft_strtrim(ft_substr(argv, 0, index), "+");
	value = ft_substr(argv, index + 1, ft_strlen(argv) - index);
	if (ft_issamechar(value, '$'))
		value = ft_itoa(getpid());
	if (ft_getenv(var) && !ft_strchr(argv, '+'))
		update_env_var(var, value, g_minish.env);
	else if (ft_getenv(var) && argv[index - 1] == '+')
		update_env_var(var, ft_strjoin(ft_getenv(var), value), g_minish.env);
	else if (ft_strchr(argv, '='))
		create_env_var(ft_strjoin(ft_strjoin(var, "="), value), &g_minish.env);
}

int	ft_export(char **argv)
{
	int		i;

	i = 0;
	if (!argv[1])
		return (export_list(), 0);
	while (*(++argv))
	{
		if (!check_var(*argv))
		{
			print_error("g_minish","export", *argv, "not a valid identifier");
			exit_status(1);
		}
		else
			add_arg_to_env(*argv);
	}
	return (0);
}
