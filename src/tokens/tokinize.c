/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:02:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/07 00:23:27 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_operator(const char *str)
{
	return (!strncmp(str, "<<", 2)
		|| !strncmp(str, ">>", 2)
		|| *str == '<'
		|| *str == '>'
		|| *str == '|');
}

t_type	get_operator_type(const char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0)
		return T_HERDOC;
	if (ft_strncmp(str, ">>", 2) == 0)
		return T_APPEND;
	if (*str == '<')
		return T_IN;
	if (*str == '>')
		return T_OUT;
	if (*str == '|')
		return T_PIPE;
	return (T_WORD);
}

char	*extract_word(char **input)
{
	char	*start;
	char	quote = 0;
	size_t	len;

	start = *input;
	while (**input)
	{
		if (!quote && is_operator(*input))
			break;
		if (!quote && ft_isspace(**input))
			break;
		if (**input == '\'' || **input == '"')
		{
			if (!quote)
				quote = **input;
			else if (**input == quote) quote = 0;
		}
		(*input)++;
	}
	len = *input - start;
	return (ft_substr(start, 0, len));
}

t_token *tokenize(char *input)
{
	t_token	*head;
	t_token	*token;
	t_type	type;
	char	*word;
	int	length;

	head = NULL;
	while (*input)
	{
		skip_spaces(&input);
		if (is_operator(input))
		{
			type = get_operator_type(input);
			if (type == T_HERDOC || type == T_APPEND)
				length = 2;
			else
				length = 1;
			word = strndup(input, length);
			if (!word)
				return (clear_tokens(&head), NULL);
			token = new_token(word, type);
			free(word);
			if (!token)
				return (clear_tokens(&head), NULL);
			token_add_back(&head, token);
			input += length;
		}
		else
		{
			word = extract_word(&input);
			if (!word)
				return (clear_tokens(&head), NULL);
			token = new_token(word, T_WORD);
			free(word);
			if (!token)
				return (clear_tokens(&head), NULL);
			token_add_back(&head, token);
		}
	}
	return (head);
}


t_token	*process_tokenize(char *input, t_env *env)
{
	char	*trimmed_input;
	char	*env_var;
	t_token	*tokens;

	trimmed_input = ft_strtrim(input, " \t\n\v\f\r");
	free(input);
	if (!trimmed_input)
		return (NULL);
	if (trimmed_input[0] == '$')
	{
		env_var = get_env_var(env, trimmed_input + 1);
		free(trimmed_input);
		if (!env_var)
			return (NULL);
		if (ft_strchr(env_var, '|'))
			trimmed_input = env_var;
		else
		{
			trimmed_input = ft_strdup(env_var);
			free(env_var);
		}
	}
	tokens = tokenize(trimmed_input);
	free(trimmed_input);
	return tokens;
}
