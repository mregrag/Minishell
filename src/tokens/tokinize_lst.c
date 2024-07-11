/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:02:54 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/11 02:27:50 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*new_token(char *value, t_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		malloc_error();
	new_token->value = ft_strdup(value);
	if (!new_token->value)
		(free(new_token), malloc_error());
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	token_add_back(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!*head)
		*head = new_token;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
}

void	clear_tokens(t_token **head)
{
	t_token	*current;
	t_token	*next;

	current = *head;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*head = NULL;
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
