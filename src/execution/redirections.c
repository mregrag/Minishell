/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:38:38 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/02 18:56:21 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	output_redirection(t_node *node, t_env *env)
{
	if (node->right && node->right->cmd)
	{
		if (node->fd_out == -1 || node->fd_in == -1)
			return (exit_status(1, env), 0);
		if (node->type == T_OUT)
			node->fd_out = ft_open_output(node->right->cmd[0]);
		else if (node->type == T_APPEND)
			node->fd_out = ft_open_append(node->right->cmd[0]);
		if (node->fd_out == -1 || node->fd_in == -1)
			return (exit_status(1, env), 0);
	}
	return (1);
}

static int	input_redirection(t_node *node, t_env *env)
{
	if (node->right && node->right->cmd)
	{
		if (node->fd_in == -1)
			return (exit_status(1, env), 0);
		if (node->type == T_IN)
			node->fd_in = ft_open_input(node->right->cmd[0]);
		if (node->fd_in == -1)
			return (exit_status(1, env), 0);
	}
	return (1);
}

int	preorder_input_redirection(t_node *node, t_env *env)
{
	if (!node)
		return (0);
	if (!input_redirection(node, env))
		return (0);
	preorder_input_redirection(node->left, env);
	preorder_input_redirection(node->right, env);
	return (1);
}

int	preorder_output_redirection(t_node *node, t_env *env)
{
	if (!node)
		return (0);
	if (!output_redirection(node, env))
		return (exit_status(1, env), 0);
	preorder_output_redirection(node->left, env);
	preorder_output_redirection(node->right, env);
	return (1);
}

int	handle_redirections(t_node **node, t_env *env)
{
	if (!preorder_input_redirection(*node, env))
		return (0);
	if (!preorder_output_redirection(*node, env))
		return (0);
	preoredr_duplicat_file(*node, env);
	if (is_redirection((*node)->type))
	{
		while (*node && (*node)->left)
		{
			if ((*node)->fd_in == -1 || (*node)->fd_out == -1)
				return (0);
			*node = (*node)->left;
		}
	}
	return (1);
}
