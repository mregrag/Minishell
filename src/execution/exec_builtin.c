/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:49:46 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/11 22:08:43 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_builtin(t_node *node, t_env *env)
{
	if (!node->cmd || !node->cmd[0])
		return (0);
	if (ft_strcmp(node->cmd[0], "echo") == 0)
		return (ft_echo(node, env));
	else if (ft_strcmp(node->cmd[0], "env") == 0)
		return (ft_env(node, env));
	else if (ft_strcmp(node->cmd[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(node->cmd[0], "cd") == 0)
		return (ft_cd(node, env));
	else if (ft_strcmp(node->cmd[0], "exit") == 0)
		return (ft_exit(node, env));
	else if (ft_strcmp(node->cmd[0], "unset") == 0)
		return (ft_unset(node, env));
	else if (ft_strcmp(node->cmd[0], "export") == 0)
		return (ft_export(node, env));
	return (0);
}
