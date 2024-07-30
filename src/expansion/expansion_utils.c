/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 21:49:59 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/29 20:50:49 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*remov_quotes(char *str)
{
	char	*ret;
	size_t	i;
	size_t	j;
	int		double_q;
	int		single_q;

	ret = malloc(strlen(str) + 1);
	if (!ret)
		malloc_error();
	i = 0;
	j = 0;
	double_q = 0;
	single_q = 0;
	while (str[i])
	{
		if (str[i] == '"' && !single_q)
			double_q = !double_q;
		else if (str[i] == '\'' && !double_q)
			single_q = !single_q;
		else
			ret[j++] = str[i];
		i++;
	}
	ret[j] = '\0';
	return (free(str), ret);
}

char	*handle_final_case(char *ret)
{
	size_t	i;
	char	*temp;

	i = 0;
	if (ft_strchr(ret, '\'') || ft_strchr(ret, '"'))
		while (ret[i] == '$')
			i++;
	if (i % 2 != 0)
	{
		temp = ft_substr(ret, 1, ft_strlen(ret) - 1);
		free(ret);
		ret = temp;
	}
	if (!ft_strlen(ret))
		return (free(ret), NULL);
	temp = remov_quotes(ret);
	return (temp);
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

char	*handle_double_quotes(char *ret, char *str, size_t *i, t_env *env)
{
	char	*content;
	char	*sub;
	char	*new_ret;

	(*i)++;
	content = ft_strdup("");
	if (!content)
		return (ret);
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			content = handle_dollar(content, str, i, env);
		else
		{
			sub = ft_substr(str, *i, 1);
			new_ret = ft_strjoin_free(content, sub);
			content = new_ret;
			(*i)++;
		}
	}
	(*i) += (str[*i] == '"');
	new_ret = ft_strjoin_three("\"", content, "\"");
	free(content);
	return (ft_strjoin_free(ret, new_ret));
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
