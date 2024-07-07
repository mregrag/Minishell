/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 21:49:59 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/07 22:19:23 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remov_quotes(char *str)
{
	char	*ret;
	size_t	i;
	size_t	j;
	int		in_quotes;

	i = 0;
	j = 0;
	in_quotes = 0;
	ret = malloc(ft_strlen(str) + 1);
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && (!in_quotes || (in_quotes && str[i + 1] == '\'')))
		{
			in_quotes = !in_quotes;
			i += in_quotes;
		}
		else
			ret[j++] = str[i];
		i++;
	}
	ret[j] = '\0';
	return (free(str), ret);
}

char	*handle_single_quotes(char *ret, char *str, size_t *i)
{
	size_t	start;
	char	*content;
	char	*new_ret;

	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'')
		(*i)++;
	content = ft_substr(str, start, *i - start);
	if (!content)
		return (ret);
	new_ret = ft_strjoin(ret, content);
	free(content);
	if (new_ret)
		return (free(ret), new_ret);
	return (ret);
}

char *handle_double_quotes(char *ret, char *str, size_t *i, t_env *env)
{
	size_t	start;
	char	*content;
	char	*new_ret;

	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			ret = handle_dollar(ret, str, i, env);
		else
			(*i)++;
	}
	if (str[*i] == '"')
		(*i)++;
	content = ft_substr(str, start, *i - start);
	if (!content)
		return (ret);
	new_ret = ft_strjoin(ret, content);
	free(content);
	if (new_ret)
		return (free(ret), new_ret);
	return (ret);
}

char	*handle_normal(char *ret, char *str, size_t *i)
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
	free(substr);
	if (new_ret)
		return (free(ret), new_ret);
	return (ret);
}
