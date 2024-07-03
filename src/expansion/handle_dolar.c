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

char	*handle_dollar(char *ret, char *str, size_t *i, t_env *env)
{
	char	*var;
	char	*val = NULL;
	size_t	start;

	start = ++(*i);
	if (ft_isdigit(str[*i]) || str[*i] == '@')
		return ((*i)++, ft_strdup(ret));
	if (str[*i] == '?')
	{
		val = get_env_var(env, "?");
		ret = ft_strjoin(ret, val);
		return (ft_free(&val), (*i)++, ret);
	}
	if (!(ft_isalnum(str[*i]) || str[*i] == '_'))
		return (ft_strjoin(ret, "$"));
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	var = ft_substr(str, start, *i - start);
	val = ft_strtrim(get_env_var(env, var), " \t\n\v\r\f");
	ft_free((void *)&var);
	if (!val)
		return (ft_free(&val), NULL);
	ret = ft_strjoin(ret, val);
	return (ft_free(&val), ret);
}
