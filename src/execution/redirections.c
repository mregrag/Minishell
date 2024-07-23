/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:05:58 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/23 13:07:34 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	heredoc_redirection(t_node *node, t_env *env)
{
	if (node->type == T_HERDOC)
	{
		if (node->right && node->right->cmd && node->right->cmd[0])
			node->fd_in = heredoc(node->right, env);
		if (node->fd_in == -1)
			return (0);
	}
	return (1);
}

static int	output_input_redirection(t_node *node)
{
	if (node->type == T_OUT || node->type == T_APPEND || node->type == T_IN)
	{
		if (node->right && node->right->cmd && node->right->cmd[0])
		{
			if (node->type == T_OUT)
				node->fd_out = ft_open_output(node->right->cmd[0]);
			else if (node->type == T_APPEND)
				node->fd_out = ft_open_append(node->right->cmd[0]);
			else if (node->type == T_IN)
				node->fd_in = ft_open_input(node->right->cmd[0]);
			if (node->fd_out == -1 || node->fd_in == -1)
				return (0);
		}
	}
	return (1);
}

void	preorder_traversal_hearedoc(t_node *node, t_env *env)
{
	if (!node || g_sig == -1)
		return ;
	if (!heredoc_redirection(node, env))
		return ;
	preorder_traversal_hearedoc(node->left, env);
	preorder_traversal_hearedoc(node->right, env);
	return ;
}

void	preorder_traversal_input_output(t_node *node)
{
	if (!node)
		return ;
	if (!output_input_redirection(node))
		return ;
	preorder_traversal_input_output(node->left);
	preorder_traversal_input_output(node->right);
}

int	handle_redirections(t_node *node, t_env *env)
{
	if (!dfs_handle_redirections(node, env))
		return (0);
	return (1);
}
