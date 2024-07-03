/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:02:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/03 23:30:01 by mregrag          ###   ########.fr       */
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

t_token	*tokenize_input(char *input, t_env *env)
{
	t_token	*tokens;
	char	*s;
	char	*v;

	tokens = NULL;
	s = ft_strtrim(input, " \t\n\v\r\f");
	v = s;
	if (v[0] == '$' && is_var_in_env(env, ++v))
	{
		v = get_env_var(env, v);
		if (ft_strchr(v, '|'))
			return (token_add_back(&tokens, new_token(v, T_WORD)), tokens);
	}
	while (*s)
	{
		if (ft_isspace(*s))
			skip_spaces(&s);
		if (!separator(&s, &tokens))
			return (clear_token(&tokens), NULL);
	}
	return (tokens);
}

