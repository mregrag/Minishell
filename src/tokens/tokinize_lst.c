/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:02:54 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/08 15:38:15 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*new_token(char *value, t_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		malloc_error();
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	token_add_back(t_token **tokens, t_token *token)
{
	t_token	*current;

	if (!*tokens)
		*tokens = token;
	else
	{
		current = *tokens;
		while (current->next)
			current = current->next;
		current->next = token;
	}
}

void	clear_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	current = *tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

void	free_token(t_token *token)
{
	if (token)
	{
		if (token->value)
		{
			free(token->value);
			token->value = NULL;
		}
		free(token);
	}
}

int	ft_lstsize_token(t_token *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
