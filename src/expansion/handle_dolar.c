/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dolar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:14:43 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/12 23:56:40 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_var_name(const char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = strndup(str, i);
	return (var_name);
}

static char	*expand_var(char *ret, char *var_value, int dollar_count)
{
	char	*new_ret;
	int		i;

	new_ret = ft_strdup("");
	i = -1;
	while (++i < (dollar_count - 1) / 2)
		new_ret = ft_strjoin(new_ret, "$");
	if (var_value)
		new_ret = ft_strjoin(new_ret, var_value);
	ret = ft_strjoin_free(ret, new_ret);
	if (ft_is_empty_string(ret))
		return (ret);
	return (ret);
}

char	*handle_dollar(char *ret, char **str, int flag, t_env *env)
{
	char	*var_name;
	char	*var_value;
	int		dollar_count;

	dollar_count = 0;
	while ((*str)[dollar_count] == '$')
		dollar_count++;
	*str += dollar_count;
	if (ft_isdigit(**str) || **str == '@')
		return ((*str)++, ft_strjoin(ret, "$"));
	if (**str == '?')
	{
		var_value = get_env_var(env, "?");
		ret = ft_strjoin(ret, var_value);
		return ((*str)++, ret);
	}
	if (!ft_isalnum(**str) && **str != '_')
		return (ft_strjoin(ret, "$"));
	if (dollar_count % 2 == 0)
		return (ft_strjoin(ret, strndup(*str - dollar_count, dollar_count)));
	var_name = get_var_name(*str);
	if (flag)
		var_value = get_env_var(env, var_name);
	else
		var_value = get_env_var_list(env, var_name);
	*str += ft_strlen(var_name);
	free(var_name);
	return (expand_var(ret, var_value, dollar_count));
}
