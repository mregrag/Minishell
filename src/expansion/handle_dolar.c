/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dolar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:14:43 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/03 19:39:08 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *handle_dollar(char *ret, char *str, size_t *i, t_env *env) {
    char *var;
    char *val = NULL;
    size_t start;
    char *new_ret;

    start = ++(*i);
    if (ft_isdigit(str[*i]) || str[*i] == '@') {
        (*i)++;
        return ret;
    }
    if (str[*i] == '?') {
        val = get_env_var(env, "?");
        if (!val) return ret; // Return ret as is if val is NULL
        new_ret = ft_strjoin(ret, val);
        free(val);
        free(ret);
        (*i)++;
        return new_ret;
    }
    if (!(ft_isalnum(str[*i]) || str[*i] == '_')) {
        new_ret = ft_strjoin(ret, "$");
        free(ret);
        return new_ret;
    }
    while (ft_isalnum(str[*i]) || str[*i] == '_') {
        (*i)++;
    }
    var = ft_substr(str, start, *i - start);
    if (!var) return ret; // Return ret as is if var is NULL
    val = get_env_var(env, var);
    free(var);
    if (!val) return ret; // Return ret as is if val is NULL
    new_ret = ft_strjoin(ret, val);
    free(ret);
    free(val);
    return new_ret;
}