/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 21:49:59 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/04 20:44:53 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *remov_quotes(char *str)
{
    char *ret;
    size_t i, j;
    int in_double_quotes = 0;
    int in_single_quotes = 0;

    if (!str)
        return NULL;

    ret = malloc(strlen(str) + 1);
    if (!ret)
    {
        free(str);
        return NULL;
    }

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
    free(str);
    return ret;
}

char *handle_single_quotes(char *ret, char *str, size_t *i)
{
    size_t start;
    char *content;
    char *new_ret;

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
    {
        free(ret);
        return new_ret;
    }
    return ret;
}

char *handle_double_quotes(char *ret, char *str, size_t *i, t_env *env)
{
    char *temp;
    char *content;
    char *sub;
    char *new_temp;
    char *new_ret;

    (*i)++;
    temp = strdup(""); // Initialize temp to an empty string
    if (!temp)
        return ret;

    while (str[*i] && str[*i] != '"')
    {
        if (str[*i] == '$')
        {
            new_temp = handle_dollar(temp, str, i, env);
            free(temp); // Free the old temp
            temp = new_temp;
        }
        else
        {
            sub = ft_substr(str, *i, 1);
            new_temp = ft_strjoin(temp, sub);
            free(temp); // Free the old temp
            free(sub);
            temp = new_temp;
            (*i)++;
        }
    }
    if (str[*i] == '"')
        (*i)++;
    content = ft_strjoin_three("\"", temp, "\"");
    new_ret = ft_strjoin(ret, content);
    free(temp);
    free(content);
    if (new_ret)
    {
        free(ret);
        return new_ret;
    }
    return ret;
}

char *handle_normal(char *ret, char *str, size_t *i)
{
    size_t start;
    char *substr;
    char *new_ret;

    start = *i;
    while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
        (*i)++;
    substr = ft_substr(str, start, *i - start);
    if (!substr)
        return ret;
    new_ret = ft_strjoin(ret, substr);
    free(substr);
    if (new_ret)
    {
        free(ret);
        return new_ret;
    }
    return ret;
}
