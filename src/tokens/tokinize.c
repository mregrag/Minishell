/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:02:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/03 15:33:33 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*extract_operator(char **input, t_type type)
{
	char	*start;
	char	*operator;
	int		length;

	start = *input;
	if (type == T_HERDOC || type == T_APPEND)
		length = 2;
	else
		length = 1;
	operator = ft_substr(start, 0, length);
	if (!operator)
		return (NULL);
	*input += length;
	return (operator);
}

static int	add_operator_token(char **input, t_token **tokens, t_type type)
{
	char	*word;

	word = extract_operator(input, type);
	if (!word)
		return (0);
	token_add_back(tokens, new_token(word, type));
	return (1);
}

static int	add_word_token(char **input, t_token **tokens, t_env *env)
{
	char	*word;
	char	*expanded_word;

	word = extract_word(input);
	if (!word)
		return (0);
	if (ft_strchr(word, '$') && !ft_strchr(word, '=') && !ft_strchr(word, ' '))
	{
		expanded_word = expansion_dollar(word, env);
		if (!add_split_tokens(tokens, expanded_word))
		{
			free(expanded_word);
			return (free(word), free(expanded_word), 0);
		}
		(free(expanded_word), free(word));
	}
	else
		token_add_back(tokens, new_token(word, T_CMD));
	return (1);
}

t_token	*create_tokens(char *input, t_env *env)
{
	t_token	*tokens;
	t_type	type;

	tokens = NULL;
	if (!check_quotes(&input))
		return (NULL);
	while (*input)
	{
		skip_spaces(&input);
		type = get_operator_type(input);
		if (is_operator(input))
		{
			if (!add_operator_token(&input, &tokens, type))
				return (clear_tokens(&tokens), NULL);
		}
		else
		{
			if (!add_word_token(&input, &tokens, env))
				return (clear_tokens(&tokens), NULL);
		}
	}
	return (tokens);
}

t_token	*tokenize_input(char *input, t_env *env)
{
	char	*new_input;
	t_token	*tokens;

	tokens = NULL;
	new_input = ft_strtrim(input, " \t\n\v\f\r");
	free(input);
	tokens = create_tokens(new_input, env);
	return (free(new_input), tokens);
}
