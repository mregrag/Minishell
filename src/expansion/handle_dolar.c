/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dolar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:14:43 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/11 07:09:20 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*handle_special_cases(char *ret, char *str, size_t *i)
{
	// char	*new_ret;

	if (ft_isdigit(str[*i]) || str[*i] == '@')
		return ((*i)++, ret);
	// else if (!ft_isalnum(str[*i]) || str[*i] != '_')
	// {
	// 	new_ret = ft_strjoin(ret, "$");
	// 	return (free(ret), new_ret);
	// }
	return (NULL);
}

static char	*handle_env_var(char *ret, char *str, size_t *i, t_env *env)
{
	char	*var;
	char	*val;
	char	*new_ret;
	size_t	start;

	start = *i;
	while ((ft_isalnum(str[*i]) || str[*i] == '?') || str[*i] == '_')
		(*i)++;
	var = ft_substr(str, start, *i - start);
	val = get_env_var(env, var);
	if (!val)
		return (free(var), ret);
	new_ret = ft_strjoin_free(ret, val);
	return (free(var), new_ret);
}

char	*handle_dollar(char *ret, char *str, size_t *i, t_env *env)
{
	char	*result;
	size_t	count;
	size_t	start;

	start = *i;
	count = 0;
	while (str[*i] == '$')
	{
		count++;
		(*i)++;
	}
	if (count > 1)
	{
		ret = consecutive_dollars(ret, str, i, count);
		if (!ret || count % 2 == 0)
			return (ret);
	}
	result = handle_special_cases(ret, str, i);
	if (result)
		return (result);
	return (handle_env_var(ret, str, i, env));
}
