/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:51:41 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/03 19:38:27 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *handle_quotes(char *ret, char *str, size_t *i, t_env *env)
{
    char quote;
    char *content = NULL;
    char *temp = NULL;
    size_t start;

    temp = ft_strdup("");
    if (!temp)
        return NULL;
    quote = str[*i];
    start = (*i)++;
    while (str[*i] && str[*i] != quote)
    {
        if (str[*i] == '$') {
            char *new_temp = handle_dollar(temp, str, i, env);
            if (!new_temp) {
                ft_free(temp);
                return NULL;
            }
            ft_free(temp);
            temp = new_temp;
        } else {
            char *next_char = ft_substr(str, *i, 1);
            if (!next_char) {
                ft_free(temp);
                return NULL;
            }
            char *new_temp = ft_strjoin(temp, next_char);
            ft_free(next_char);
            ft_free(temp);
            temp = new_temp;
            if (!temp) {
                return NULL;
            }
            (*i)++;
        }
    }
    if (str[*i] == quote) {
        (*i)++;
    }
    char *quote_char = ft_substr(str, start, 1);
    if (!quote_char) {
        ft_free(temp);
        return NULL;
    }
    char *first_part = ft_strjoin(quote_char, temp);
    ft_free(quote_char);
    ft_free(temp);
    if (!first_part)
        return NULL;
    content = ft_strjoin(first_part, quote_char);
    ft_free(first_part);
    if (!content)
        return NULL;
    char *new_ret = ft_strjoin(ret, content);
    ft_free(content);

    if (!new_ret)
        return NULL;
    ft_free(ret);
    return new_ret;
}

char *handle_quotes_dilim(char *ret, const char *str, size_t *i)
{
    char quote;
    char *content;
    char *temp;
    size_t start;

    temp = ft_strdup("");
    if (!temp)
        return NULL;
    quote = str[*i];
    start = (*i)++;
    while (str[*i] && str[*i] != quote)
    {
        char *next_char = ft_substr(str, *i, 1);
        if (!next_char) {
            free(temp);
            return NULL;
        }
        char *new_temp = ft_strjoin(temp, next_char);
        free(next_char);
        free(temp);
        temp = new_temp;
        if (!temp) {
            return NULL;
        }
        (*i)++;
    }
    if (str[*i] == quote)
        (*i)++;
    char *quote_char = ft_substr(str, start, 1);
    if (!quote_char) {
        free(temp);
        return NULL;
    }
    content = ft_strjoin(quote_char, temp);
    free(quote_char);
    free(temp);

    if (!content)
        return NULL;
    char *new_ret = ft_strjoin(ret, content);
    free(content);
    if (!new_ret)
        return NULL;
    free(ret);
    return new_ret;
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
