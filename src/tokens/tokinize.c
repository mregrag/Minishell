/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:02:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/12 23:38:50 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

bool has_space_between_quotes(const char *str)
{
    char quote = 0;
    bool in_quotes = false;
    bool has_content = false;

    while (*str) {
        if (*str == '\'' || *str == '"')
	{
            if (!in_quotes)
	    {
                quote = *str;
                in_quotes = true;
                has_content = false;
            } else if (*str == quote) {
                return has_content;
            }
        } else if (in_quotes) {
            if (isspace(*str)) {
                if (has_content) {
                    return true;
                }
            } else {
                has_content = true;
            }
        }
        str++;
    }
    return false;
}

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

static int	add_operator_token(char **input, t_token **tokens)
{
	char	*operator;
	t_type	type;

	type = get_operator_type(*input);
	operator = extract_operator(input, type);
	if (!operator)
		return (clear_tokens(tokens), 0);
	token_add_back(tokens, new_token(operator, type));
	return (1);
}

static int	add_word_token(char **input, t_token **tokens, t_env *env, int flag)
{
	char	*word;
	char	*expand_word;

	word = extract_word(input);
	if (flag)
		return (token_add_back(tokens, new_token(word, T_CMD)), 1);
	expand_word = expansion_input(word, env);
	if (!expand_word)
		return (free(word), free(expand_word), clear_tokens(tokens), 0);
	if (!has_space_between_quotes(word))
	{
		if (!split_into_tokens(tokens, expand_word))
			return (free(word), free(expand_word), clear_tokens(tokens), 0);
		return (free(expand_word), free(word), 1);
	}
	token_add_back(tokens, new_token(expand_word, T_CMD));
	return (free(word), 1);
}

t_token	*tokenize_input(char *input, t_env *env)
{
	t_token	*tokens;
	char	*new_input;
	char	*current;
	int		flag;

	tokens = NULL;
	new_input = ft_strtrim(input, " \t\n\v\f\r");
	current = new_input;
	flag = 0;
	if (!check_quotes(new_input))
		return (free(current), free(input), NULL);
	while (*current)
	{
		skip_spaces(&current);
		if (get_operator_type(current) == T_HERDOC)
			flag = 1;
		if (is_operator(current))
		{
			if (!add_operator_token(&current, &tokens))
				return (free(input), free(new_input), NULL);
		}
		else if (!add_word_token(&current, &tokens, env, flag))
			return (free(input), free(new_input), NULL);
	}
	return (free(new_input), free(input), tokens);
}
