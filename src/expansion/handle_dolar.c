/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dolar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:14:43 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/10 04:05:41 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*handle_special_cases(char *ret, char *str, size_t *i, t_env *env)
{
	char	*val;
	char	*new_ret;

	if (ft_isdigit(str[*i]) || str[*i] == '@')
		return ((*i)++, ret);
	if (str[*i] == '?')
	{
		val = get_env_var(env, "?");
		if (!val)
			return (ret);
		new_ret = ft_strjoin_free(ret, val);
		(*i)++;
		return (new_ret);
	}
	if (!(ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		new_ret = ft_strjoin(ret, "$");
		free(ret);
		return (new_ret);
	}
	return (NULL);
}

static char	*handle_env_var(char *ret, char *str, size_t *i, t_env *env)
{
	char	*var;
	char	*val;
	char	*new_ret;
	size_t	start;

	start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	var = ft_substr(str, start, *i - start);
	if (!var)
		return (ret);
	val = get_env_var(env, var);
	free(var);
	if (!val)
		return (NULL);
	new_ret = ft_strjoin_free(ret, val);
	return (new_ret);
}

char	*handle_dollar(char *ret, char *str, size_t *i, t_env *env)
{
	char	*result;

	(*i)++;
	result = handle_special_cases(ret, str, i, env);
	if (result)
		return (result);
	return (handle_env_var(ret, str, i, env));
}
