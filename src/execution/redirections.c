/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:38:38 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/30 13:27:46 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	input_redirection(t_node *node, t_env *env)
{
	if (node->right && node->right->cmd)
		if (node->type == T_IN)
			node->fd_in = ft_open_input(node->right->cmd[0]);
	if (node->fd_in == -1)
		return (exit_status(1, env), 0);
	return (1);
}

static int	output_redirection(t_node *node, t_env *env)
{
	if (node->right && node->right->cmd)
	{
		if (node->type == T_OUT)
			node->fd_out = ft_open_output(node->right->cmd[0]);
		else if (node->type == T_APPEND)
			node->fd_out = ft_open_append(node->right->cmd[0]);
	}
	if (node->fd_out == -1)
		return (exit_status(1, env), 0);
	return (1);
}

void	preorder_input(t_node *node, t_env *env)
{
	if (!node)
		return ;
	if (!input_redirection(node, env))
		return ;
	preorder_input(node->left, env);
	preorder_input(node->right, env);
}

void	preorder_output(t_node *node, t_env *env)
{
	if (!node)
		return ;
	if (!output_redirection(node, env))
		return ;
	preorder_output(node->left, env);
	preorder_output(node->right, env);
}

int	handle_redirections(t_node **node, t_env *env)
{
	if (is_redirection((*node)->type))
	{
		if (!preoredr_duplicat_file(*node, env))
			return (0);
		while (*node && (*node)->left)
			*node = (*node)->left;
	}
	return (1);
}
