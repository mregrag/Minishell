/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 03:29:28 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/14 03:40:47 by mregrag          ###   ########.fr       */
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
		new_ret = ft_strjoin_free(ret, val);
		return ((*i)++, new_ret);
	}
	else if (str[*i] == '_')
		return ((*i)++, ret);
	else if (!ft_isalnum(str[*i]))
	{
		new_ret = ft_strjoin(ret, "$");
		return (free(ret), new_ret);
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
	val = get_env_var(env, var);
	(free(var));
	if (!val)
		return (ret);
	new_ret = ft_strjoin(ret, val);
	return (new_ret);
}

char	*handle_dollar_her(char *ret, char *str, size_t *i, t_env *env)
{
	char	*result;
	int	count;
	size_t	start;
	int	j;

	j= -1;
	start = *i;
	count = 0;
	while (str[*i] == '$')
	{
		count++;
		(*i)++;
	}
	result = handle_special_cases(ret, str, i, env);
	if (result)
		return (result);
	if (count % 2 == 0)
		return (ft_strjoin_free(ret, ft_substr(str, start, count)));
	result = handle_env_var(ret, str, i,env);
	while (count-- > 1)
		result = ft_strjoin_free(ft_strdup("$"), result);
	return (result);
}
