/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:23:34 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/15 02:51:55 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

t_node	*new_node(t_type type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		malloc_error();
	node->type = type;
	node->cmd = NULL;
	node->left = NULL;
	node->right = NULL;
	node->flag = 0;
	return (node);
}

void	free_tree(t_node *node)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	if (node->cmd)
	{
		while (node->cmd[i])
		{
			free(node->cmd[i]);
			i++;
		}
		free(node->cmd);
	}
	free_tree(node->left);
	free_tree(node->right);
	free(node);
}

t_node	*create_redire(t_token *tokens, t_token *tmp, t_env *env)
{
	t_node	*node;

	node = new_node(tokens->type);
	tokens = tokens->next->next;
	node->left = parse_redire(tokens, env);
	node->right = parse_file(tmp->next, tmp->type, env);
	free_token(tmp);
	return (node);
}
