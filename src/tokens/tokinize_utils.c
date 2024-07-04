/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:05:33 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/01 22:07:41 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_separator(t_type type, char **line, t_token **tokens, char *value)
{
	t_token	*token;

	token = new_token(value, type);
	if (!token)
		return (0);
	token_add_back(tokens, token);
	(*line)++;
	if (type == T_HERDOC || type == T_APPEND)
		(*line)++;
	return (1);
}

int process_word(char **line, t_token **tokens)
{
    char    *tmp;
    char    *value;
    t_token *token;
    size_t  i;

    tmp = *line;
    i = 0;
    while (tmp[i] && !is_separator(tmp + i))
    {
        if (ft_isquotes(tmp[i]))
        {
            if (!skip_quotes(tmp, &i))
            {
                print_error("minish", "unexpected EOF `", NULL, NULL);
                return 0;
            }
        }
        else
            i++;
    }
    value = ft_substr(tmp, 0, i);
    if (!value)
        return 0;
    token = new_token(value, T_WORD);
    free(value);
    if (!token)
        return 0;
    *line += i;
    token_add_back(tokens, token);
    return 1;
}