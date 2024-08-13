/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 21:49:59 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/13 20:03:15 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remov_quotes(char *str)
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

char	*handle_single_quotes(char *ret, char **str)
{
	char	*start;
	char	*content;

	start = *str;
	(*str)++;
	while (**str && **str != '\'')
		(*str)++;
	if (**str == '\'')
		(*str)++;
	content = ft_substr(start, 0, *str - start);
	return (ft_strjoin_free(ret, content));
}

char	*handle_double_quotes(char *ret, char **str, t_env *env)
{
	char	*content;
	char	*new_ret;

	(*str)++;
	content = ft_strdup("");
	if (!content)
		malloc_error();
	while (**str && **str != '"')
	{
		if (**str == '$')
			content = handle_dollar(content, str, 0, env);
		else
		{
			new_ret = ft_strjoin_free(content, ft_substr(*str, 0, 1));
			content = new_ret;
			(*str)++;
		}
	}
	if (**str == '"')
		(*str)++;
	new_ret = ft_strjoin_three("\"", content, "\"");
	return (free(content), ft_strjoin_free(ret, new_ret));
}

char	*handle_normal(char *ret, char **str)
{
	char	*start;
	char	*substr;
	char	*new_ret;

	start = *str;
	while (**str && **str != '\'' && **str != '"' && **str != '$')
		(*str)++;
	substr = ft_substr(start, 0, *str - start);
	if (!substr)
		return (ret);
	new_ret = ft_strjoin(ret, substr);
	free(substr);
	if (new_ret)
		return (free(ret), new_ret);
	return (ret);
}
