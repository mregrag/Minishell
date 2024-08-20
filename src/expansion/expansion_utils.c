/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 21:49:59 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/20 06:48:34 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_quotes(char *str)
{
	char	*ret;
	size_t	i;
	size_t	j;
	char	quotes;

	i = 0;
	j = 0;
	ret = ft_calloc(1 + ft_strlen(str), sizeof(char));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quotes = str[i++];
			while (str[i] && str[i] != quotes)
				ret[j++] = str[i++];
			if (str[i])
				i++;
		}
		else
			ret[j++] = str[i++];
	}
	ret[j] = '\0';
	return (ret);
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
	(*i) += (str[*i] == '"');
	content = ft_substr(str, start, *i - start);
	if (!content)
		return (NULL);
	new_ret = ft_strjoin_free(ret, content);
	return (new_ret);
}

char	*handle_double_quotes(char *ret, char *str, size_t *i, t_env *env)
{
	char	*content;
	char	*new_ret;

	(*i)++;
	content = ft_strdup("");
	if (!content)
		return (NULL);
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			content = handle_dollar(content, str, i, env);
		else
		{
			new_ret = ft_strjoin_free(content, ft_substr(str, *i, 1));
			content = new_ret;
			(*i)++;
		}
	}
	(*i) += (str[*i] == '"');
	new_ret = ft_strjoin_three("\"", content, "\"");
	return (free(content), ft_strjoin_free(ret, new_ret));
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
		return (NULL);
	new_ret = ft_strjoin_free(ret, substr);
	if (!new_ret)
		return (NULL);
	return (new_ret);
}
