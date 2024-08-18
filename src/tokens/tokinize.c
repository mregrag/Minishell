/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 23:26:40 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/18 06:17:10 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*extract_operator(char **input, t_type type)
{
	char	*start;
	char	*operator;
	int		length;

	start = *input;
	length = (type == T_HERDOC || type == T_APPEND) ? 2 : 1;
	operator = ft_substr(start, 0, length);
	if (!operator)
		return (NULL);
	*input += length;
	return (operator);
}

char	*remove_double_quotes(char *str)
{
	char	*ret;
	size_t	i;
	size_t	j;
	char	quotes;

	i = 0;
	j = 0;
	ret = ft_calloc(1 + ft_strlen(str), sizeof(char));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"')
		{
			quotes = str[i++];
			while (str[i] && str[i] != quotes)
				ret[j++] = str[i++];
			if (str[i])
				i++;
		}
		else
			ret[j++] = str[i++];
	}
	ret[j] = '\0';
	return (free(str), ret);
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

int	dollar_position(const char *str)
{
	char	*equals;

	equals = ft_strchr(str, '=');
	if (!equals)
		return (0);
	return (equals[1] == '$');
}

static int	add_to_list_token(char *expand, bool dollar, t_token **tokens)
{
	char	*word;
	t_type	type;

	while (expand && *expand)
	{
		skip_spaces(&expand);
		type = get_operator_type(expand);
		if (type >= T_PIPE && type <= T_HERDOC)
			word = extract_operator(&expand, type);
		else
			word = extract_word(&expand);
		if (dollar)
			token_add_back(tokens, new_token(remove_double_quotes(word), 0));
		else
			token_add_back(tokens, new_token(remove_quotes(word), type));
	}
	return (1);
}

static int	process_word(char *word, t_token **tokens, bool flag, t_env *env)
{
	char	*expand;

	expand = expand_variable(word, flag, env);
	if (flag && ft_strchr(word, '$'))
	{
		if (dollar_position(word) == 1)
			token_add_back(tokens, new_token(expand, get_operator_type(word)));
		else
			add_to_list_token(expand, true, tokens);
	}
	else
	{
		if (ft_strchr(word, '$'))
			add_to_list_token(expand, true, tokens);
		else
			add_to_list_token(expand, false, tokens);
	}
	return (free(expand), 1);
}

static int	create_tokens(char *input, t_token **tokens, t_env *env)
{
	char	*word;
	t_type	type;
	bool	flag;

	flag = false;
	while (*input)
	{
		skip_spaces(&input);
		type = get_operator_type(input);
		if (type >= T_PIPE && type <= T_HERDOC)
			word = extract_operator(&input, type);
		else
			word = extract_word(&input);
		if (!ft_strcmp(word, "export") || type == T_HERDOC)
			flag = true;
		process_word(word, tokens, flag, env);
	}
	return (free(word), 1);
}

t_token	*tokenize_input(char *input, t_env *env)
{
	t_token	*tokens;
	char	*new_input;

	tokens = NULL;
	new_input = ft_strtrim(input, " \t\n\f\r");
	if (!check_quotes(new_input))
		return (NULL);
	create_tokens(new_input, &tokens, env);
	free(input);
	free(new_input);
	return (tokens);
}
