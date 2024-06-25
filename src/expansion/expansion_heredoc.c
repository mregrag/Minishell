/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:12:56 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/25 20:31:41 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*handle_quotes(char *ret, const char *str, size_t *i)
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
			temp = handle_dollar(temp, str, i);
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
	(free(temp), free(content));
	return (ret);
}

char	*expansion_file(char *str)
{
	size_t	i;
	char	*ret;

	ret = strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			ret = handle_single_quotes(ret, str, &i);
		else if (str[i] == '"')
			ret = handle_double_quotes(ret, str, &i);
		else if (str[i] == '$')
			ret = handle_dollar(ret, str, &i);
		else
			ret = handle_normal(ret, str, &i);
	}
	return (remov_quotes(ret));
}

char	*expansion_content(char *str)
{
	size_t	i;
	char	*ret;

	ret = strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			ret = handle_quotes(ret, str, &i);
		else if (str[i] == '$')
			ret = handle_dollar(ret, str, &i);
		else
			ret = handle_normal(ret, str, &i);
	}
	return (ret);
}
