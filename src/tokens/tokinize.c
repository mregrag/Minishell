/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:02:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/11 20:31:23 by mkoualil         ###   ########.fr       */
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
	free(word);
	return (1);
}

static int	handle_word(char **input, t_token **tokens)
{
	char	*word;

	word = extract_word(input);
	if (!word)
		return (0);
	token_add_back(tokens, new_token(word, T_CMD));
	free(word);
	return (1);
}

static t_token	*create_single_token(char *str)
{
	t_token	*token;

	token = new_token(str, T_CMD);
	free(str);
	return (token);
}

t_token	*tokenize(char *input)
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
	char	*trimmed;
	char	*env_var;
	t_token	*tokens;

	tokens = NULL;
	trimmed = ft_strtrim(input, " \t\n\v\f\r");
	free(input);
	if (!trimmed)
		return (NULL);
	if (trimmed[0] == '$' && is_var_in_env(env , trimmed + 1))
	{
		env_var = get_env_var(env, trimmed + 1);
		free(trimmed);
		if (!env_var)
			return (NULL);
		if (check_operators(env_var))
			return (create_single_token(env_var));
		trimmed = ft_strdup(env_var);
		free(env_var);
		if (!trimmed)
			return (NULL);
	}
	tokens = tokenize(trimmed);
	return (free(trimmed), tokens);
}
