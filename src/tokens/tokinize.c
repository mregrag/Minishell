/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:02:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/08 18:01:24 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*extract_word(char **input)
{
	char	*start;
	size_t	len;
	char	quote;

	quote = 0;
	start = *input;
	while (**input)
	{
		if (!quote && is_operator(*input))
			break ;
		if (!quote && ft_isspace(**input))
			break ;
		if (ft_isquotes(**input))
		{
			if (!quote)
				quote = **input;
			else if (**input == quote)
				quote = 0;
		}
		(*input)++;
	}
	len = *input - start;
	return (ft_substr(start, 0, len));
}

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	t_type	type;
	char	*word;

	if (!check_quotes(&input))
		return (NULL);
	while (*input)
	{
		skip_spaces(&input);
		if (is_operator(input))
		{
			type = get_operator_type(input);
			if (type == T_HERDOC || type == T_APPEND)
				input += 2;
			else
				input += 1;
			word = ft_strdup(input);
			if (!word)
				return (clear_tokens(&tokens), NULL);
			(token_add_back(&tokens, new_token(word, type)), free(word));
		}
		else
		{
			word = extract_word(&input);
			if (!word)
				return (clear_tokens(&tokens), NULL);
			(token_add_back(&tokens, new_token(word, T_WORD)), free(word));
		}
	}
	return (tokens);
}

t_token	*create_single_token(char *str)
{
	t_token	*token;

	token = new_token(str, T_WORD);
	free(str);
	return (token);
}

t_token	*process_tokenize(char *input, t_env *env)
{
	char	*trimmed;
	char	*env_var;
	t_token	*tokens;

	tokens = NULL;
	if (!input)
		return (NULL);
	trimmed = ft_strtrim(input, " \t\n\v\f\r");
	free(input);
	if (!trimmed)
		return (NULL);
	if (trimmed[0] == '$')
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
