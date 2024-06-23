/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:23:34 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/23 16:20:36 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_lstsize_token(t_token *lst)
{
	int	counter;

	counter = 0;
	while (lst != NULL)
	{
		counter++;
		lst = lst->next;
	}
	return (counter);
}

t_node	*new_node(t_token_type type)
{
	t_node		*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->cmd = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	free_tree(t_node *node)
{
	int		i;

	i = 0;
	if (!node)
		return ;
	if (node->type == T_WORD && node->cmd)
	{
		while (node->cmd && node->cmd[i])
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

t_node	*create_redire(t_token **tokens, t_token *tmp)
{
	t_node	*node;

	node = new_node((*tokens)->type);
	*tokens = (*tokens)->next->next;
	node->left = parse_redire(tokens);
	node->right = create_file(tmp->next);
	free(tmp->value);
	free(tmp);
	return (node);
}

void	creat_cmd(t_node *node, t_token **tokens, int count)
{
	int		i;
	t_token	*tmp;

	i = 0;
	while (i < count)
	{
		node->cmd[i] = expand_cmd((*tokens)->value);
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp->value);
		free(tmp);
		i++;

	}
	node->cmd[count] = NULL;
}

