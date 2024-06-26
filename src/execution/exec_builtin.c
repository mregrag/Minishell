/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:49:46 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/01 19:47:58 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(t_node *node)
{
	if (ft_strcmp(node->cmd[0], "echo") == 0)
		return (ft_echo(node));
	else if (ft_strcmp(node->cmd[0], "env") == 0)
		return (ft_env(node));
	else if (ft_strcmp(node->cmd[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(node->cmd[0], "cd") == 0)
		return (ft_cd(node));
	else if (ft_strcmp(node->cmd[0], "exit") == 0)
		return (ft_exit(node));
	else if (ft_strcmp(node->cmd[0], "unset") == 0)
		return (ft_unset(node));
	else if (ft_strcmp(node->cmd[0], "export") == 0)
		return (ft_export(node));
	return (0);
}
