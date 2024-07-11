/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:47:28 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/11 05:41:54 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_numeric(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	error(char *cmd, char *arg, char *message)
{
	print_error(cmd, arg, message, NULL);
	exit(255);
}

int	ft_exit(t_node *node, t_env *env)
{
	long	exit_code;

	ft_putendl_fd("exit", 2);
	if (node->cmd[1])
	{
		if (!is_numeric(node->cmd[1]))
			error(node->cmd[0], node->cmd[1], "numeric argument required");
		exit_code = ft_atol(node->cmd[1]);
		if (exit_code == LONG_MAX || exit_code == LONG_MIN)
			error(node->cmd[0], node->cmd[1], "numeric argument required");
		if (node->cmd[2])
		{
			print_error("minish", node->cmd[0], "too many arguments", NULL);
			exit_status(1, env);
			return (1);
		}
		exit((unsigned char)exit_code);
	}
	exit((unsigned char)ft_atoi(get_env_var(env, "?")));
}
