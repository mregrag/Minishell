/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:05:33 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/13 06:02:14 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	split_into_tokens(t_token **tokens, char *expanded_word)
{
	char	**split_words;
	int		i;

	i = 0;
	split_words = NULL;
	split_words = ft_split(expanded_word, ' ');
	if (ft_is_empty_string(expanded_word))
	{
		token_add_back(tokens, new_token(ft_strdup(expanded_word), T_CMD));
		return (free(split_words), 1);
	}
	while (split_words[i])
	{
		token_add_back(tokens, new_token(split_words[i], T_CMD));
		i++;
	}
	return (free(split_words), 1);
}

int	check_quotes(char *line)
{
	size_t	i;

	i = 0;
	while ((line)[i])
	{
		if (ft_isquotes(line[i]) && !skip_quotes(line, &i))
			return (print_error("minish", "unexpected EOF `", NULL, NULL), 0);
		else
			i++;
	}
	return (1);
}


int	is_hase_qoutes(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len < 2)
		return (0);
	if (str[0] == '"' && str[len - 1] == '"')
		return (1);
	return (0);
}

t_type	get_operator_type(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0)
		return (T_HERDOC);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (T_APPEND);
	if (*str == '<')
		return (T_IN);
	if (*str == '>')
		return (T_OUT);
	if (*str == '|')
		return (T_PIPE);
	return (T_CMD);
}

