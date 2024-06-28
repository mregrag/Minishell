/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:47:28 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/28 23:03:22 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int	is_numeric(char *s)
{
	while (*s)
		if (!ft_isdigit(*s++))
			return (0);
	return (1);
}

int	ft_exit(t_node *node)
{
	if (node->cmd[1] && !is_numeric(node->cmd[1]))
	{
		ft_putstr_fd("exit\n", 2);
		print_error(node->cmd[0], node->cmd[1], "numeric argument reguierd", NULL);
		exit(255);
	}
	else if (ft_strlen_arg(node->cmd) > 2)
	{
		printf("exit\n");
		print_error("minish", node->cmd[0], "too many argument", NULL);
		update_env_var("?", "1", node);
	}
	else if (ft_strlen_arg(node->cmd) == 1)
	{
		printf("exit\n");
		exit(0);
	}
	else
	{
		printf("exit\n");
		exit(ft_atoi(node->cmd[1]));
	}
	return (0);
}
