/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:12:56 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/29 22:31:37 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*handle_quotes(char *ret, const char *str, size_t *i, t_node *node)
{
	char	quote;
	char	*content;
	char	*temp;
	size_t	start;

	temp = ft_strdup("");
	quote = str[*i];
	start = (*i)++;
	while (str[*i] && str[*i] != quote)
	{
		if (str[*i] == '$')
			temp = handle_dollar(temp, str, i, node);
		else
		{
			temp = ft_strjoin(temp, ft_substr(str, *i, 1));
			(*i)++;
		}
	}
	if (str[*i] == quote)
		(*i)++;
	content = ft_strjoin(ft_substr(str, start, 1), temp);
	content = ft_strjoin(content, ft_substr(str, start, 1));
	ret = ft_strjoin(ret, content);
	(ft_free(&temp), ft_free(&content));
	return (ret);
}

static char	*handle_quotes_dilim(char *ret, const char *str, size_t *i)
{
	char	quote;
	char	*content;
	char	*temp;
	size_t	start;

	temp = ft_strdup("");
	quote = str[*i];
	start = (*i)++;
	while (str[*i] && str[*i] != quote)
	{
		temp = ft_strjoin(temp, ft_substr(str, *i, 1));
		(*i)++;
	}
	if (str[*i] == quote)
		(*i)++;
	content = ft_strjoin(ft_substr(str, start, 1), temp);
	content = ft_strjoin(content, ft_substr(str, start, 1));
	ret = ft_strjoin(ret, content);
	(free(temp), free(content));
	return (ret);
}


char *handle_str(char *ret, const char *str, size_t *i)
{
	size_t	start;
	char	*substr;
	char	*new_ret;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"')
		(*i)++;
	substr = ft_substr(str, start, *i - start);
	if (!substr)
		return (ret);
	new_ret = ft_strjoin(ret, substr);
	ft_free(&substr);
	if (new_ret)
		return (ft_free((void **)&ret), new_ret);
	else
		return (ret);
}
char	*expansion_dilim(char *str, t_node *node)
{
	size_t	i;
	char	*ret;

	ret = strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			node->flag = 1;
			ret = handle_quotes_dilim(ret, str, &i);
		}
		else
			ret = handle_str(ret, str, &i);
	}
	return (remov_quotes(ret));
}

char	*expansion_content(char *str, t_node *node)
{
	size_t	i;
	char	*ret;

	ret = strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			ret = handle_quotes(ret, str, &i, node);
		else if (str[i] == '$')
			ret = handle_dollar(ret, str, &i, node);
		else
			ret = handle_normal(ret, str, &i);
	}
	return (ret);
}
