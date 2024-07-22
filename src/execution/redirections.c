/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:05:58 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/22 15:46:44 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	input_redirection(t_node *node, t_env *env)
{
	if (node->type == T_IN || node->type == T_HERDOC)
	{
		if (node->type == T_IN)
		{
			if (node->right && node->right->cmd && node->right->cmd[0])
				node->fd_in = ft_open_input(node->right->cmd[0]);
		}
		else if (node->type == T_HERDOC)
		{
			if (node->right)
				node->fd_in = heredoc(node->right, env);
		}
		if (node->fd_in == -1)
			return (exit_status(1, env), 0);
	}
	return (1);
}

static int	output_redirection(t_node *node, t_env *env)
{
	if (node->type == T_OUT || node->type == T_APPEND)
	{
		if (node->right)
		{
			if (node->type == T_OUT)
				node->fd_out = ft_open_output(node->right->cmd[0]);
		}
		if (node->right && node->right->cmd && node->right->cmd[0])
		{
			if (node->type == T_APPEND)
				node->fd_out = ft_open_append(node->right->cmd[0]);
		}
		if (node->fd_out == -1)
			return (exit_status(1, env), 0);
	}
	return (1);
}

void	preorder_traversal(t_node *node, t_env *env)
{
	if (!node || g_sig == -1)
		return ;
	if (!input_redirection(node, env) || !output_redirection(node, env))
		return ;
	preorder_traversal(node->left, env);
	preorder_traversal(node->right, env);
}

int	handle_redirections(t_node *node)
{
	while (node && node->left)
	{
		if (node->fd_in == -1 || node->fd_out == -1)
			return (0);
		if (node->fd_in != 0)
			if (ft_dup2(node->fd_in, STDIN_FILENO) < 0)
				return (0);
		if (node->fd_out != 1)
			if (ft_dup2(node->fd_out, STDOUT_FILENO) < 0)
				return (0);
		node = node->left;
	}
	return (1);
}

