/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:23:34 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/22 17:51:04 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	node->fd_in = 0;
	node->fd_out = 1;
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

void	fill_cmd(t_node *node, t_token *tokens, t_env *env, int count)
{
	int		i;
	int		j;
	char	*expanded;
	t_token	*tmp;

	i = 0;
	j = 0;
	while (i < count)
	{
		expanded = expansion_input(tokens->value, env);
		if (expanded != NULL)
			node->cmd[j++] = expanded;
		tmp = tokens;
		tokens = tokens->next;
		free_token(tmp);
		i++;
	}
	node->cmd[j] = NULL;
}

t_node	*create_redire(t_token *tokens, t_token *tmp, t_env *env)
{
	t_node	*node;

	node = new_node(tokens->type);
	tokens = tokens->next->next;
	node->left = parse_redirection(tokens, env);
	node->right = parse_file(tmp->next, tmp->type, env);
	free_token(tmp);
	return (node);
}
