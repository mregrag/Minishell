/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:05:33 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/05 18:55:11 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	append_separator(t_token_type type, char **line, t_token **tokens, char *value)
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


int	append_identifier(char **line, t_token **tokens)
{
	char	*tmp;
	char	*value;
	t_token	*token;
	size_t	i;

	tmp = *line;
	i = 0;
	while (tmp[i] && !is_separator(tmp + i))
	{
		if (ft_isquotes(tmp[i]))
		{
			if (!skip_quotes(tmp, &i))
				return (quotes_error(tmp[i]), 0);
		}
		else
			i++;
	}
	value = ft_substr(tmp, 0, i);
	if (!value)
		return (0);
	token = new_token(value, T_WORD);
	if (!token)
		return (free(value), 0);
	*line += i;
	return (token_add_back(tokens, token), 1);
}
