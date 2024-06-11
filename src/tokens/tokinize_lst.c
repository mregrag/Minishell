/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:02:54 by mregrag           #+#    #+#             */
/*   Updated: 2024/05/24 17:26:26 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	return (token);
}

void	token_add_back(t_token **lst, t_token *new_token)
{
	t_token	*last;

	if (!*lst)
		*lst = new_token;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new_token;
	}
}

void	clear_token(t_token **lst)
{
	t_token	*currunt;
	t_token	*next;

	currunt = *lst;
	if (!currunt)
		return ;
	while (currunt)
	{
		free(currunt->value);
		next = currunt->next;
		free(currunt);
		currunt = next;
	}
	*lst = NULL;
}
