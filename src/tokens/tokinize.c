/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:02:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/21 16:50:10 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_operator(char **input, t_token **tokens)
{
	t_type	type;
	char	*word;
	char	*start;

	start = *input;
	type = get_operator_type(*input);
	if (type == T_HERDOC || type == T_APPEND)
		*input += 2;
	else
		*input += 1;
	word = ft_substr(start, 0, *input - start);
	if (!word)
		return (0);
	token_add_back(tokens, new_token(word, type));
	return (1);
}

static int	handle_word(char **input, t_token **tokens)
{
	char	*word;

	word = extract_word(input);
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

t_token	*tokenize_input(char *input, t_env *env)
{
	char	*new_input;
	char	*value;
	t_token	*tokens;

	tokens = NULL;
	new_input = ft_strtrim(input, " \t\n\v\f\r");
	free(input);
	if (new_input[0] == '$' && is_var_in_env(env, new_input + 1))
	{
		value = get_env_var(env, new_input + 1);
		free(new_input);
		if (!value)
			return (NULL);
		if (check_operators(value))
			return (new_token(value, T_CMD));
		new_input = ft_strdup(value);
		free(value);
		if (!new_input)
			return (NULL);
	}
	tokens = creat_tokens(new_input);
	return (free(new_input), tokens);
}
