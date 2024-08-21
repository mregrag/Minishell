/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 06:19:47 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/21 00:15:49 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	token_dollar(char *word, t_token **tokens, int flag, t_env *env)
{
	char	*expand;

	expand = expand_variable(word, flag, env);
	if (!expand)
		return (0);
	if (count_quotes(word) % 2 == 0)
		extract_dollar_tokens(expand, true, tokens);
	else
		token_add_back(tokens, new_token(remove_quotes(expand), 0));
	return (free(expand), 1);
}

static int	token_file(char *word, t_token **tokens, int flag, t_env *env)
{
	char	*expand;
	t_type	type;

	type = get_operator_type(word);
	expand = expand_variable(word, flag, env);
	if (!expand)
		return (0);
	if (flag == 2)
		token_add_back(tokens, new_token(ft_strdup(expand), type));
	else if (ft_strchr(word, '$') && flag == 3 && ft_whitespace(expand))
		token_add_back(tokens, new_token(NULL, 0));
	else
		token_add_back(tokens, new_token(remove_quotes(expand), type));
	return (free(expand), 1);
}

static int	token_export(char *word, t_token **tokens, int flag, t_env *env)
{
	char	*expand;
	char	*tmp;

	expand = expand_variable(word, flag, env);
	if (!expand)
		return (0);
	tmp = remove_quotes(expand);
	if (ft_strchr(word, '$') && !whitespace_before_equal(expand))
		token_add_back(tokens, new_token(ft_strdup(expand), 0));
	else if (whitespace_before_equal(expand))
		extract_dollar_tokens(tmp, false, tokens);
	else
		token_add_back(tokens, new_token(ft_strdup(tmp), 0));
	return (free(expand), free(tmp), 1);
}

static int	token_default(char *word, t_token **tokens, int flag, t_env *env)
{
	char	*expand;
	t_type	type;

	type = get_operator_type(word);
	expand = expand_variable(word, flag, env);
	token_add_back(tokens, new_token(remove_quotes(expand), type));
	return (free(expand), 1);
}

int	analyse_token(char *word, t_token **tokens, int flag, t_env *env)
{
	if (ft_strchr(word, '$') && flag == 0)
		return (token_dollar(word, tokens, flag, env));
	else if (flag == 3 || flag == 2)
		return (token_file(word, tokens, flag, env));
	else if (flag == 1)
		return (token_export(word, tokens, flag, env));
	else
		return (token_default(word, tokens, flag, env));
}
