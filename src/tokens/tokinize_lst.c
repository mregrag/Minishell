/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:02:54 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/05 15:53:18 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



t_token *new_token(char *value, t_type type)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token) return NULL;

    token->value = strdup(value);
    if (!token->value) {
        free(token);
        return NULL;
    }

    token->type = type;
    token->next = NULL;
    return token;
}


void token_add_back(t_token **head, t_token *new_token)
{
    if (!*head) {
        *head = new_token;
        return;
    }

    t_token *current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = new_token;
}

void free_tokens(t_token *head)
{
    while (head)
    {
        t_token *temp = head;
        head = head->next;
        free(temp->value);
        free(temp);
    }
}

void clear_token(t_token **tokens)
{
    t_token *current;
    t_token *next;

    if (!tokens || !*tokens)
        return;

    current = *tokens;
    while (current && current->next)
    {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }

    *tokens = NULL;
}

int ft_lstsize_token(t_token *lst)
{
    int count;

    count = 0;
    while (lst)
    {
        count++;
        lst = lst->next;
    }
    return count;
}
