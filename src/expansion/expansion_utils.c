/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 21:49:59 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/17 01:45:51 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remov_quotes(char *str)
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
	// if (!ft_strlen(ret))
	// 	return (free(ret), NULL);
	temp = remov_quotes(ret);
	return (temp);
}
// int has_space_in_quotes(const char *str)
// {
// 	char quote_type = 0;
// 	bool in_quotes = false;
// 	bool escaped = false;
// 	bool has_space = false;
//
// 	while (*str) {
// 		if (*str == '\\' && !escaped) {
// 			escaped = true;
// 			str++;
// 			continue;
// 		}
//
// 		if ((*str == '\'' || *str == '"') && !escaped) {
// 			if (!in_quotes) {
// 				in_quotes = true;
// 				quote_type = *str;
// 				has_space = false;
// 			} else if (*str == quote_type) {
// 				in_quotes = false;
// 				if (has_space)
// 					return 1;
// 			}
// 		} else if (in_quotes) {
// 			if (ft_isspace(*str))
// 				has_space = true;
// 		}
//
// 		escaped = false;
// 		str++;
// 	}
//
// 	return 0;
// }
//

char	*handle_single_quotes(char *ret, char *str, size_t *i)
{
	size_t	start;
	char	*content;

	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	(*i) += (str[*i] == '"');
	content = ft_substr(str, start, *i - start);
	return (ft_strjoin_free(ret, content));
}

char	*handle_double_quotes(char *ret, char *str, size_t *i, t_env *env)
{
	char	*content;
	char	*new_ret;

	(*i)++;
	content = ft_strdup("");
	if (!content)
		malloc_error();
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
		return (ret);
	new_ret = ft_strjoin(ret, substr);
	free(substr);
	if (new_ret)
		return (free(ret), new_ret);
	return (ret);
}

