/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:02:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/30 11:36:26 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_word(char **input, t_token **tokens)
{
	char	*word;

	word = extract_word(input);
	if (!word)
		return (0);
	token_add_back(tokens, new_token(word, T_CMD));
	return (1);
}

static int	handle_word_dollar(char **input, t_token **tokens)
{
	char	*word;

	word = extract_word_dollar(input);
	if (!word)
		return (0);
	token_add_back(tokens, new_token(word, T_CMD));
	return (1);
}

static t_token	*creat_tokens(char *input)
{
	t_token	*tokens;

	tokens = NULL;
	if (!check_quotes(&input))
		return (NULL);
	while (*input)
	{
		skip_spaces(&input);
		if (is_operator(input))
		{
			if (!handle_operator(&input, &tokens))
				return (clear_tokens(&tokens), NULL);
		}
		else
			if (!handle_word(&input, &tokens))
				return (clear_tokens(&tokens), NULL);
	}
	return (tokens);
}

static t_token	*tokenize_dollar(char *input)
{
	t_token	*tokens;

	tokens = NULL;
	if (!check_quotes(&input))
		return (NULL);
	while (*input)
	{
		skip_spaces(&input);
		if (!handle_word_dollar(&input, &tokens))
		{
			clear_tokens(&tokens);
			return (NULL);
		}
	}
	return (tokens);
}

t_token	*tokenize_input(char *input, t_env *env)
{
	char	*new_input;
	char	*value;
	t_token	*tokens;

	tokens = NULL;
	value = NULL;
	new_input = ft_strtrim(input, " \t\n\v\f\r");
	free(input);
	if (new_input[0] == '$' && new_input[1] != '$')
	{
		if (!check_quotes(&input))
			return (free(new_input), NULL);
		value = expansion_input(new_input, env);
		free(new_input);
		if (!value)
			return (NULL);
		tokens = tokenize_dollar(value);
		return (free(value), tokens);
	}
	tokens = creat_tokens(new_input);
	return (free(new_input), tokens);
}
