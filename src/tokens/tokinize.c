/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:02:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/24 20:21:33 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_separator(char **line, t_token **token_list)
{
	if (!ft_strncmp(*line, "<<", 2))
		return (append_separator(T_HERDOC, line, token_list, "<<"));
	else if (!ft_strncmp(*line, ">>", 2))
		return (append_separator(T_APPEND, line, token_list, ">>"));
	else if (!ft_strncmp(*line, "<", 1))
		return (append_separator(T_IN, line, token_list, "<"));
	else if (!ft_strncmp(*line, ">", 1))
		return (append_separator(T_OUT, line, token_list, ">"));
	else if (!ft_strncmp(*line, "|", 1))
		return (append_separator(T_PIPE, line, token_list, "|"));
	else
		return (append_identifier(line, token_list));
}

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	char	*s;

	tokens = NULL;
	s = ft_strtrim(input, " \t\n\v\r\f");
	free(input);
	if (s[0] == '$')
		s = ft_strjoin("", ++s);
	while (*s)
	{
		if (ft_isspace(*s))
			ft_skip_spaces(&s);
		if (!ft_separator(&s, &tokens))
			return (clear_token(&tokens), NULL);
	}
	return (tokens);
}
