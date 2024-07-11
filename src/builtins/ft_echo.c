/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:16:11 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/11 21:50:13 by mkoualil         ###   ########.fr       */
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
	int	newline;

	i = 1;
	newline = 0;
	while (node->cmd[i] && check_option(node->cmd[i]) == 1)
	{
		newline = 1;
		i++;
	}
	while (node->cmd[i])
	{
		ft_putstr_fd(node->cmd[i], 1);
		set_env_var(env, "_", node->cmd[i]);
		exit_status(0, env);
		if (node->cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline == 0)
		ft_putstr_fd("\n", 1);
	return (1);
}
