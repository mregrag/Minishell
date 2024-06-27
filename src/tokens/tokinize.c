/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:02:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/27 22:14:27 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	separator(char **line, t_token **token_list)
{
	if (!ft_strncmp(*line, "<<", 2))
		return (add_separator(T_HERDOC, line, token_list, "<<"));
	else if (!ft_strncmp(*line, ">>", 2))
		return (add_separator(T_APPEND, line, token_list, ">>"));
	else if (!ft_strncmp(*line, "<", 1))
		return (add_separator(T_IN, line, token_list, "<"));
	else if (!ft_strncmp(*line, ">", 1))
		return (add_separator(T_OUT, line, token_list, ">"));
	else if (!ft_strncmp(*line, "|", 1))
		return (add_separator(T_PIPE, line, token_list, "|"));
	else
		return (process_word(line, token_list));
}

t_token	*tokenize_input(char *input, t_node *node)
{
	t_token	*tokens;
	char	*s;

	(void)node;
	tokens = NULL;
	s = ft_strtrim(input, " \t\n\v\r\f");
	if (s[0] == '$' && s[1] && is_env_var(++s, node->env))
	{
		s = ft_strjoin("", ft_getenv(s, node->env));
	}
	free(input);
	while (*s)
	{
		if (ft_isspace(*s))
			skip_spaces(&s);
		if (!separator(&s, &tokens))
			return (clear_token(&tokens), NULL);
	}
	return (tokens);
}
