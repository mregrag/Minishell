/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:05:33 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/09 21:16:14 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_split_tokens(t_token **tokens, char *expanded_word)
{
	char	**split_words;
	int		i;

	i = 0;
	split_words = ft_split(expanded_word, ' ');
	if (!split_words || !split_words[0])
		token_add_back(tokens, new_token(ft_strdup(expanded_word), T_CMD));
	else
	{
		while (split_words[i])
		{
			printf("split  = %s\n", split_words[i]);
			token_add_back(tokens, new_token(split_words[i], T_CMD));
			i++;
		}
	}
	free(split_words);
	return (1);
}

int	check_quotes(char *line)
{
	size_t	i;

	i = 0;
	while ((line)[i])
	{
		if (ft_isquotes((line)[i]) && !skip_quotes(line, &i))
			return (print_error("minish", "unexpected EOF `", NULL, NULL), 0);
		else
			i++;
	}
	return (1);
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
	if (*str == ' ')
		return (T_PIPE);
	else
		return (T_CMD);
	return (T_CMD);
}
