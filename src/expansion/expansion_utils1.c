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
    char *temp;
    char *content;
    char *new_ret;
    size_t start;

    quote = str[*i];
    start = (*i)++;
    temp = ft_strdup("");
    if (!temp) return ret;

    while (str[*i] && str[*i] != quote)
    {
        if (str[*i] == '$')
        {
            char *dollar_result = handle_dollar(temp, str, i, env);
            free(temp);
            temp = dollar_result;
        }
        else
        {
            char *substr = ft_substr(str, *i, 1);
            if (!substr)
            {
                free(temp);
                return ret;
            }
            char *new_temp = ft_strjoin(temp, substr);
            free(temp);
            free(substr);
            temp = new_temp;
            (*i)++;
        }
        if (!temp) return ret;
    }

    if (str[*i] == quote)
        (*i)++;

    char *opening_quote = ft_substr(str, start, 1);
    char *closing_quote = ft_substr(str, start, 1);
    if (!opening_quote || !closing_quote)
    {
        (free(temp), free(opening_quote), free(closing_quote));
        return ret;
    }
    content = ft_strjoin(opening_quote, temp);
    free(opening_quote);
    free(temp);
    if (!content)
    {
        free(closing_quote);
        return ret;
    }
    char *new_content = ft_strjoin(content, closing_quote);
    free(content);
    free(closing_quote);
    if (!new_content) return ret;
    new_ret = ft_strjoin(ret, new_content);
    free(new_content);
    free(ret);
    return new_ret;
}

char *handle_quotes_dilim(char *ret, const char *str, size_t *i)
{
    char quote;
    char *temp;
    char *content;
    char *new_ret;
    size_t start;

    temp = ft_strdup("");
    if (!temp) return ret;

    quote = str[*i];
    start = (*i)++;
    while (str[*i] && str[*i] != quote)
    {
        char *substr = ft_substr(str, *i, 1);
        if (!substr)
        {
            free(temp);
            return ret;
        }
        char *new_temp = ft_strjoin(temp, substr);
        free(temp);
        free(substr);
        temp = new_temp;
        if (!temp) return ret;
        (*i)++;
    }
    if (str[*i] == quote)
        (*i)++;

    char *opening_quote = ft_substr(str, start, 1);
    char *closing_quote = ft_substr(str, start, 1);
    if (!opening_quote || !closing_quote)
    {
        free(temp);
        free(opening_quote);
        free(closing_quote);
        return ret;
    }
    content = ft_strjoin(opening_quote, temp);
    free(opening_quote);
    free(temp);
    if (!content)
    {
        free(closing_quote);
        return ret;
    }
    char *new_content = ft_strjoin(content, closing_quote);
    free(content);
    free(closing_quote);
    if (!new_content) return ret;

    new_ret = ft_strjoin(ret, new_content);
    free(new_content);
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
