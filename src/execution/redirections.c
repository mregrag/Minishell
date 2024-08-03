/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:38:38 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/03 16:22:15 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	input_output_redirection(t_node *node)
{
	while (node)
	{
		if (node->type == T_IN)
			node->fd_in = ft_open_input(node->right->cmd[0]);
		else if (node->type == T_OUT)
			node->fd_out = ft_open_output(node->right->cmd[0]);
		else if (node->type == T_APPEND)
			node->fd_out = ft_open_append(node->right->cmd[0]);
		if (node->fd_out == -1 || node->fd_in == -1)
			return ;
		node = node->left;
	}
}

int	handle_redirections(t_node **node, t_env *env)
{
	if (is_redirection((*node)->type))
	{
		input_output_redirection(*node);
		if (!preoredr_duplicat_file(*node, env))
			return (0);
		while (*node && (*node)->left)
			*node = (*node)->left;
	}
	return (1);
}
