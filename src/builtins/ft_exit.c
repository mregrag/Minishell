/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:47:28 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/03 18:03:39 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_valid_number(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static void	error(char *cmd, char *arg, char *message)
{
	print_error("minish", cmd, arg, message);
	exit(255);
}

static int	is_long(char *str)
{
	int				i;
	unsigned long	result;
	int				sign;

	result = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != 0)
	{
		result = result * 10 + (str[i] - 48);
		if (result > 9223372036854775807 && sign == 1)
			return (0);
		else if ((result) > 9223372036854775808UL && sign == -1)
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_node *node, t_env *env)
{
	ft_putendl_fd("exit", 2);
	if (node->cmd[1])
	{
		if (!is_valid_number(node->cmd[1]))
			error(node->cmd[0], node->cmd[1], "numeric argument required");
		if (!is_long(node->cmd[1]))
			error(node->cmd[0], node->cmd[1], "numeric argument required");
		if (node->cmd[2])
		{
			print_error("minish", node->cmd[0], "too many arguments", NULL);
			exit_status(1, env);
			return (1);
		}
		exit(ft_atoi(node->cmd[1]));
	}
	exit(ft_atoi(ft_strtrim(get_env_var(env, "?"), "\"")));
}
