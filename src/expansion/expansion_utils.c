/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 21:49:59 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/06 18:46:10 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remov_quotes(char *str)
{
	char	*ret;
	size_t	i;
	size_t	j;
	int	in_double_quotes;
	int	in_single_quotes;
	in_double_quotes = 0;
	in_single_quotes = 0;
	if (!str)
		return (NULL);
	ret = malloc(strlen(str) + 1);
	if (!ret)
		return (free(str), NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (str[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
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
		return ret;
	new_ret = ft_strjoin(ret, content);
	free(content);
	if (new_ret)
		return (free(ret), new_ret);
	return (ret);
}

char	*handle_double_quotes(char *ret, char *str, size_t *i, t_env *env)
{
	char *temp = strdup("");
	if (!temp)
		return ret;

	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			char *new_temp = handle_dollar(temp, str, i, env);
			if (new_temp)
				temp = new_temp;
		}
		else
		{
			char *sub = ft_substr(str, *i, 1);
			if (sub)
			{
				char *new_temp = ft_strjoin(temp, sub);
				free(sub);
				if (new_temp)
				{
					free(temp);
					temp = new_temp;
				}
				(*i)++;
			}
		}
	}
	if (str[*i] == '"')
		(*i)++;
	char *content = ft_strjoin_three("\"", temp, "\"");
	if (content)
	{
		char *new_ret = ft_strjoin(ret, content);
		free(content);
		if (new_ret)
		{
			free(ret);
			ret = new_ret;
		}
	}
	return (free(temp), ret);
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
