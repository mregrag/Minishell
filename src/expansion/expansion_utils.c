/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 21:49:59 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/29 21:37:38 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_dollar(char *ret, const char *str, size_t *i, t_node *node)
{
	char	*var;
	char	*val = NULL;
	size_t	start;

	start = ++(*i);
	if (ft_isdigit(str[*i]) || str[*i] == '@')
		return ((*i)++, ft_strdup(ret));
	if (str[*i] == '?')
	{
		val = ft_getenv("?", node->env);
		ret = ft_strjoin(ret, val);
		return (free(val), (*i)++, ret);
	}
	if (!(ft_isalnum(str[*i]) || str[*i] == '_'))
		return (ft_strjoin(ret, "$"));
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	var = ft_substr(str, start, *i - start);
	val = ft_strtrim(ft_getenv(var, node->env), " \t\n\v\r\f");
	ft_free((void *)&var);
	if (!val)
		return (ft_free(&val), NULL);
	ret = ft_strjoin(ret, val);
	return (ft_free((void **)&val), ret);
}

char	*remov_quotes(char *str)
{
	char	*ret;
	char	quote;
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	ret = malloc(strlen(str) + 1);
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				ret[j++] = str[i++];
			i++;
		}
		else
			ret[j++] = str[i++];
	}
	ret[j] = '\0';
	return (ft_free(&str), ret);
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
	ft_free((void **)&content);
	return (ret);
}

char	*handle_double_quotes(char *ret, const char *str, size_t *i, t_node *node)
{
	char	*temp;
	char	*content;

	temp = ft_strdup("");
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			temp = handle_dollar(temp, str, i, node);
		else
		{
			temp = ft_strjoin(temp, ft_substr(str, *i, 1));
			(*i)++;
		}
	}
	if (str[*i] == '"')
		(*i)++;
	content = ft_strjoin(ft_strjoin("\"", temp), "\"");
	ret = ft_strjoin(ret, content);
	ft_free((void **)&temp);
	ft_free((void **)&content);
	return (ret);
}

char *handle_normal(char *ret, const char *str, size_t *i)
{
	size_t	start;
	char	*substr;
	char	*new_ret;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	substr = ft_substr(str, start, *i - start);
	if (!substr)
		return (ret);
	new_ret = ft_strjoin(ret, substr);
	ft_free(&substr);
	if (new_ret)
		return (ft_free(&ret), new_ret);
	else
		return (ret);
}
