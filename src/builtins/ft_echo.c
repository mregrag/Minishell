/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:16:11 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/22 21:07:17 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_options(char **s)
{
	int	i;
	int	j;

	j = 1;
	while (s[j] && s[j][0] == '-' && s[j][1] == 'n')
	{
		i = 1;
		while (s[j][i] && s[j][i] == 'n')
			i++;
		if (s[j][i] != '\0')
			break ;
		j++;
	}
	return (j);
}

int	ft_echo(t_node *node, t_env *env)
{
	int	i;
	int	newline;

	newline = 1;
	i = check_options(node->cmd);
	if (i > 1)
		newline = 0;
	while (node->cmd[i])
	{
		ft_putstr_fd(node->cmd[i], 1);
		set_env_var(env, "_", node->cmd[i]);
		exit_status(0, env);
		if (node->cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline == 1)
		ft_putstr_fd("\n", 1);
	return (1);
}
