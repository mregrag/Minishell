/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:38:38 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/29 00:42:53 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	input_redirection(t_node *node)
{
	if (node->right && node->right->cmd)
		if (node->type == T_IN)
			node->fd_in = ft_open_input(node->right->cmd[0]);
	if (node->fd_in == -1)
		return (0);
	return (1);
}

static int	output_redirection(t_node *node)
{
	if (node->right && node->right->cmd)
	{
		if (node->type == T_OUT)
			node->fd_out = ft_open_output(node->right->cmd[0]);
		else if (node->type == T_APPEND)
			node->fd_out = ft_open_append(node->right->cmd[0]);
	}
	if (node->fd_out == -1 || node->fd_in == -1)
		return (0);
	return (1);
}

int	preorder_input(t_node *node)
{
	if (!node)
		return (0);
	if (!input_redirection(node))
		return (0);
	preorder_input(node->left);
	preorder_input(node->right);
	return (1);
}

int	preorder_output(t_node *node)
{
	if (!node)
		return (0);
	if (!output_redirection(node))
		return (0);
	preorder_output(node->left);
	preorder_output(node->right);
	return (1);
}

int	handle_redirections(t_node *node, t_env *env)
{
	if (!preoredr_duplicat_file(node, env))
		return (0);
	return (1);
}
