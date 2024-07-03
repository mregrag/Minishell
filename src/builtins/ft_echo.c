/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:16:11 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/03 19:23:42 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_option(char *s)
{
	int	i;

	i = 0;
	if (s[0] != '-')
		return (0);
	i++;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_node *node, t_env *env)
{
	int	i;
	int	supp_newline;

	i = 1;
	supp_newline = 0;
	while (node->cmd[i] != NULL && check_option(node->cmd[i]) == 1)
	{
		supp_newline = 1;
		i++;
	}
	while (node->cmd[i])
	{
		ft_putstr_fd(node->cmd[i], 1);
		set_env_var(env, "_", node->cmd[i]);
		if (node->cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (supp_newline == 0)
		ft_putstr_fd("\n", 1);
	return (1);
}
