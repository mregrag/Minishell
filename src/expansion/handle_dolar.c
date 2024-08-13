/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dolar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:14:43 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/13 02:28:10 by mregrag          ###   ########.fr       */
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

static char	*expand_var(char *ret, char *var_value, int count)
{
	char	*new_ret;
	int		i;

	new_ret = ft_strdup("");
	i = -1;
	while (++i < (count - 1) / 2)
		new_ret = ft_strjoin_free(new_ret, ft_strdup("$"));
	if (var_value)
		new_ret = ft_strjoin(new_ret, var_value);
	ret = ft_strjoin_free(ret, new_ret);
	return (ret);
}

static char	*handle_special_cases(char **str, char *ret, t_env *env)
{
	char	*var_value;

	if (ft_isdigit(**str) || **str == '@')
	{
		(*str)++;
		return (ret);
	}
	if (**str == '?')
	{
		var_value = get_env_var(env, "?");
		ret = ft_strjoin_free(ret, var_value);
		(*str)++;
		return (ret);
	}
	if (!ft_isalnum(**str) && **str != '_')
		return (ft_strjoin_free(ret, ft_strdup("$")));
	return (NULL);
}

char	*handle_dollar(char *ret, char **str, int flag, t_env *env)
{
	char	*var_name;
	char	*var_value;
	char	*special_case;
	int		count;

	count = 0;
	while ((*str)[count] == '$')
		count++;
	*str += count;
	special_case = handle_special_cases(str, ret, env);
	if (special_case)
		return (special_case);
	if (count % 2 == 0)
		return (ft_strjoin_free(ret, strndup(*str - count, count)));
	var_name = get_var_name(*str);
	if (flag)
		var_value = get_env_var(env, var_name);
	else
		var_value = get_env_var_list(env, var_name);
	*str += ft_strlen(var_name);
	free(var_name);
	return (expand_var(ret, var_value, count));
}
