/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:47:28 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/25 17:07:51 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int	is_digit(char *s)
{
	while (*s)
		if (!ft_isdigit(*s++))
			return (0);
	return (1);
}

int	ft_exit(char **cmd)
{
	if (cmd[1] && !is_digit(cmd[1]))
	{
		ft_putstr_fd("exit\n", 2);
		print_error(cmd[0], cmd[1], "numeric argument reguierd", NULL);
		exit(255);
	}
	else if (ft_strlen_arg(cmd) > 2)
	{
		printf("exit\n");
		print_error("minish", cmd[0], "too many argument", NULL);
		exit_status(1);
	}
	else if (ft_strlen_arg(cmd) == 1)
	{
		printf("exit\n");
		exit(0);
	}
	else
	{
		printf("exit\n");
		exit(ft_atoi(cmd[1]));
	}
	return (0);
}
