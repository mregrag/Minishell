/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:51:41 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/12 22:11:44 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_quotes(char *ret, char **str, t_env *env)
{
	char	*new_ret;
	char	*start;

	new_ret = ft_strdup(ret);
	start = *str;
	while (**str && **str != '\n')
	{
		if (**str == '$' && *(*str + 1) && *(*str + 1) != ' ')
		{
			if (*str > start)
				new_ret = ft_strjoin_free(new_ret, ft_substr(start, 0, *str - start));
			new_ret = handle_dollar(new_ret, str, 1, env);
			start = *str;
		}
		else
			(*str)++;
	}
	if (*str > start)
		new_ret = ft_strjoin_free(new_ret, ft_substr(start, 0, *str - start));
	if (**str == '\n')
		(*str)++;
	return (free(ret), new_ret);
}

char	*handle_str(char *ret, char *str, size_t *i)
{
	size_t	start;
	char	*substr;
	char	*new_ret;

	start = *i;
	while (str[*i])
		(*i)++;
	substr = ft_substr(str, start, *i - start);
	if (!substr)
		return (ret);
	new_ret = ft_strjoin(ret, substr);
	free(substr);
	if (new_ret)
		return (free(ret), new_ret);
	else
		return (ret);
}

// char	*consecutive_dollars(char *ret, char **str, size_t count)
// {
// 	char	*result;
// 	char	*dollars;
// 	char	*start;
//
// 	start = *str - count;
// 	if (count % 2 == 0)
// 	{
// 		dollars = ft_substr(start, 0, count);
// 		if (!dollars)
// 			return (free(ret), NULL);
// 		result = ft_strjoin_free(ret, dollars);
// 		*str = start + count;
// 		return (result);
// 	}
// 	if (count % 2 != 0)
// 	{
// 		dollars = ft_substr(start, 0, count - 1);
// 		if (!dollars)
// 			return (free(ret), NULL);
// 		result = ft_strjoin_free(ret, dollars);
// 		if (!result)
// 			return (NULL);
// 		ret = result;
// 		*str = start + count - 1;
// 	}
// 	return (ret);
// }
