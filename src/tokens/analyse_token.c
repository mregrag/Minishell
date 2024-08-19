/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 06:19:47 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/19 11:01:10 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	token_dollar(char *word, t_token **tokens, int flag, t_env *env)
{
	char	*expand;
	char	*tmp;

	tmp = remove_quotes(word);
	expand = ft_strtrim(expand_variable(tmp, flag, env), " \t\n\f\r");
	printf("expan = %s\n", expand);
	if (ft_isempty(expand))
		return (free(expand), free(tmp), 1);
	if (count_quotes(word) % 2 == 0)
		add_to_list_token(expand, true, tokens);
	else
		token_add_back(tokens, new_token(ft_strdup(expand), 0));
	return (free(expand), free(tmp), 1);
}

static int	token_file(char *word, t_token **tokens, int flag, t_env *env)
{
	char	*expand;

	expand = expand_variable(word, flag, env);
	if (ft_isempty(expand))
		token_add_back(tokens, new_token(NULL, 0));
	else
		add_to_list_token(expand, false, tokens);
	return (free(expand), 1);
}

static int	token_export(char *word, t_token **tokens, int flag, t_env *env)
{
	char	*expand;
	char	*tmp;

	expand = expand_variable(word, flag, env);
	printf("ex = %s\n", expand);
	tmp = remove_quotes(expand);
	printf("tmp = %s\n", tmp);
	if (!whitespace_before_equal(tmp))
		token_add_back(tokens, new_token(ft_strdup(tmp), 0));
	else
		add_to_list_token(expand, false, tokens);
	return (free(expand), free(tmp), 1);
}

static int	token_default(char *word, t_token **tokens, int flag, t_env *env)
{
	char	*expand;

	expand = expand_variable(word, flag, env);
	add_to_list_token(expand, false, tokens);
	return (free(expand), 1);
}

int	analyse_token(char *word, t_token **tokens, int flag, t_env *env)
{
	if (ft_strchr(word, '$') && flag == 0)
		return (token_dollar(word, tokens, flag, env));
	else if (ft_strchr(word, '$') && flag == 3)
		return (token_file(word, tokens, flag, env));
	else if (flag == 1)
		return (token_export(word, tokens, flag, env));
	else
		return (token_default(word, tokens, flag, env));
}
