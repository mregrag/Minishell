/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:51:41 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/01 16:52:56 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_quotes(char *ret, char *str, size_t *i, t_node *node)
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

char	*handle_quotes_dilim(char *ret, const char *str, size_t *i)
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


char *handle_str(char *ret, char *str, size_t *i)
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
