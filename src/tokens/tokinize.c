/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 23:26:40 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/19 00:50:46 by mregrag          ###   ########.fr       */
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

int	contains_whitespace_before(const char *str)
{
	const char *equals_pos = strchr(str, '=');
	if (equals_pos == NULL)
		return (1);
	while (str < equals_pos)
	{
		if (ft_isspace((unsigned char)*str))
			return (1);
		str++;
	}
	return (0);
}

int	is_empty(const char *str)
{
	if (str == NULL)
		return (1);
	while (*str) {
		if (!ft_isspace((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}


static int	process_word(char *word, t_token **tokens, int flag, t_env *env)
{
	char	*expand;

	expand = expand_variable(word, flag, env);
	if (flag == 1)
	{
		if (!contains_whitespace_before(expand))
			token_add_back(tokens, new_token(remove_quotes(expand), 0));
		else if (contains_whitespace_before(expand))
			add_to_list_token(ft_strdup(expand), false, tokens);
		else
			token_add_back(tokens, new_token(remove_quotes(expand), 0));
	}
	else if (is_empty(expand))
		token_add_back(tokens, new_token(NULL, 0));
	else if (ft_strchr(word, '$'))
		add_to_list_token(expand, true, tokens);
	else
		add_to_list_token(expand, false, tokens);
	return (1);
}

static int	create_tokens(char *input, t_token **tokens, t_env *env)
{
	char	*word;
	t_type	type;
	int	flag;

	flag = false;
	while (*input)
	{
		skip_spaces(&input);
		type = get_operator_type(input);
		if (type >= T_PIPE && type <= T_HERDOC)
			word = extract_operator(&input, type);
		else
			word = extract_word(&input);
		if (!ft_strcmp(word, "export"))
			flag = 1;
		else if (type == T_HERDOC)
			flag = T_HERDOC;
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
		return (free(input), free(new_input), NULL);
	create_tokens(new_input, &tokens, env);
	free(input);
	free(new_input);
	return (tokens);
}
