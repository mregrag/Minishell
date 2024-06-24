/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 21:45:53 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/24 19:07:28 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_dollar(char *ret, const char *str, size_t *i)
{
	char	*var;
	char	*val;
	size_t	start;

	start = ++(*i);
	if (ft_isdigit(str[*i]) || str[*i] == '@')
		return ((*i)++, ft_strdup(ret));
	if (str[*i] == '?')
	{
		val = ft_itoa(minish.exit_status);
		ret = ft_strjoin(ret, val);
		return (free(val), (*i)++, ret);
	}
	if (!(ft_isalnum(str[*i]) || str[*i] == '_'))
		return (ft_strjoin(ret, "$"));
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	var = ft_substr(str, start, *i - start);
	val = ft_strtrim(ft_getenv(var), " \t\n\v\r\f");
	free(var);
	if (!val)
		return (ft_strdup(ret));
	ret = ft_strjoin(ret, val);
	return (free(val), ret);
}

char	*handle_single_quotes(char *ret, const char *str, size_t *i)
{
	size_t	start;
	char	*content;

	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'')
		(*i)++;
	content = ft_substr(str, start, *i - start);
	ret = ft_strjoin(ret, content);
	free(content);
	return (ret);
}

char	*handle_double_quotes(char *ret, const char *str, size_t *i)
{
	char	*temp;
	char	*content;

	temp = ft_strdup("");
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			temp = handle_dollar(temp, str, i);
		else
		{
			temp = ft_strjoin(temp, ft_substr(str, *i, 1));
			(*i)++;
		}
	}
	if (str[*i] == '"')
		(*i)++;
	content = ft_strjoin("\"", temp);
	content = ft_strjoin(content, "\"");
	ret = ft_strjoin(ret, content);
	free(temp);
	free(content);
	return (ret);
}

char	*handle_normal(char *ret, const char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_strjoin(ret, ft_substr(str, start, *i - start)));
}

char	*ft_expand(char *str)
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
