/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 23:26:40 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/17 01:51:15 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*extract_operator(char **input, t_type type)
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

static char	*extract_word(char **input)
{
	char	*start;
	size_t	len;
	char	quote;

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
	return (ft_substr(start, 0, len));
}

static int	creat_tokenes(char **input, t_token **tokens, int dolar, int flag)
{
	char	*word;
	t_type	type;

	while (input && **input)
	{
		skip_spaces(input);
		type = get_operator_type(*input);
		if (type >= T_PIPE && type <= T_HERDOC)
			word = extract_operator(input, type);
		else
			word = extract_word(input);
		if (!word)
			return (clear_tokens(tokens), 0);
		if (dolar && !flag)
			token_add_back(tokens, new_token(ft_strtrim_single(word, "\""), 0));
		else
			token_add_back(tokens, new_token(remov_quotes(word), type));
	}
	return (1);
}

t_token *tokenize_input(char *input, t_env *env)
{
	t_token	*tokens;
	char	*new_input;
	char	*current;
	int	flag;
	int	dolar;

	tokens = NULL;
	new_input = ft_strtrim(input, " \t\n\f\r");
	flag = 0;
	dolar = 0;
	if (!check_quotes(new_input))
		return NULL;
	if (ft_strnstr(new_input, "<<", ft_strlen(new_input)))
		flag = 1;
	if (ft_strchr(new_input, '$') && !ft_strchr(new_input, '='))
		dolar = 1;
	if (ft_strchr(new_input, '='))
		current = expand_export(new_input, flag, env);
	else if (flag)
		current = new_input;
	else
		current = expand_variable(new_input, flag, env);
	creat_tokenes(&current, &tokens, dolar, flag);
	return (free(input), free(new_input), tokens);
}
