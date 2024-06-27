/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:49:46 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/27 21:41:57 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(t_node *node)
{
	if (ft_strcmp(node->cmd[0], "echo") == 0)
		return (ft_echo(node), 1);
	else if (ft_strcmp(node->cmd[0], "env") == 0)
		return (ft_env(node), 1);
	else if (ft_strcmp(node->cmd[0], "pwd") == 0)
		return (ft_pwd(), 1);
	else if (ft_strcmp(node->cmd[0], "cd") == 0)
		return (ft_cd(node), 1);
	else if (ft_strcmp(node->cmd[0], "exit") == 0)
		return (ft_exit(node), 1);
	else if (ft_strcmp(node->cmd[0], "unset") == 0)
		return (ft_unset(node), 1);
	else if (ft_strcmp(node->cmd[0], "export") == 0)
		return (ft_export(node), 1);
	return (0);
}

// bool	is_builtin(char *arg)
// {
// 	if (!arg)
// 		return (false);
// 	if (!ft_strcmp(arg, "echo")
// 		|| !ft_strcmp(arg, "cd")
// 		|| !ft_strcmp(arg, "exit")
// 		|| !ft_strcmp(arg, "pwd")
// 		|| !ft_strcmp(arg, "export")
// 		|| !ft_strcmp(arg, "unset")
// 		|| !ft_strcmp(arg, "env"))
// 		return (true);
// 	return (false);
// }

