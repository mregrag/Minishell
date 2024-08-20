/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 23:26:40 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/20 06:52:41 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*extract_operator(char **input, t_type type)
{
	char	*start;
	char	*operator;
	int		len;

	start = *input;
	if (type == T_HERDOC || type == T_APPEND)
		len = 2;
	else
		len = 1;
	operator = ft_substr(start, 0, len);
	if (!operator)
		return (NULL);
	*input += len;
	return (operator);
}

static char	*extract_word(char **input)
{
	char	*start;
	size_t	len;
	char	quote;
	char	*result;

	quote = 0;
	start = *input;
	while (**input)
	{
		if (!quote && (is_operator(*input) || ft_isspace(**input)))
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
	result = ft_substr(start, 0, len);
	if (!result)
		return (NULL);
	return (result);
}

int	extract_dollar_tokens(char *expand, bool dollar, t_token **tokens)
{
	char	*word;
	t_type	type;

	while (*expand)
	{
		skip_spaces(&expand);
		type = get_operator_type(expand);
		if (type >= T_PIPE && type <= T_HERDOC)
			word = extract_operator(&expand, type);
		else
			word = extract_word(&expand);
		if (!word)
			return (0);
		if (dollar)
			token_add_back(tokens, new_token(ft_strtrim(word, "\""), 0));
		else
			token_add_back(tokens, new_token(remove_quotes(word), type));
		free(word);
	}
	return (1);
}

static int	extract_tokens(char *input, t_token **tokens, t_env *env)
{
	char	*word;
	t_type	type;
	int		flag;

	flag = 0;
	while (*input)
	{
		skip_spaces(&input);
		type = get_operator_type(input);
		if (type >= T_PIPE && type <= T_HERDOC)
			word = extract_operator(&input, type);
		else
			word = extract_word(&input);
		if (!word)
			return (0);
		if (!ft_strcmp(word, "export"))
			flag = 1;
		else if (type == T_HERDOC)
			flag = 2;
		else if (type >= T_IN && type <= T_OUT)
			flag = 3;
		analyse_token(word, tokens, flag, env);
		free(word);
	}
	return (1);
}

t_token	*tokenize_input(char *input, t_env *env)
{
	t_token	*tokens;
	char	*new_input;

	tokens = NULL;
	new_input = ft_strtrim(input, " \t\n\f\r");
	if (!check_quotes(new_input))
	{
		free(input);
		free(new_input);
		return (NULL);
	}
	if (!extract_tokens(new_input, &tokens, env))
		return ((clear_tokens(&tokens), free(input), free(new_input), NULL));
	free(input);
	free(new_input);
	return (tokens);
}
