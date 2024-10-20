/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:51:41 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/21 09:39:11 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_quotes(char *ret, char *str, size_t *i, t_env *env)
{
	char	*new_ret;
	size_t	start;
	size_t	len;

	new_ret = ft_strdup(ret);
	start = *i;
	while (str[*i] && str[*i] != '\n')
	{
		if (str[*i] == '$' && str[*i + 1] && str[*i + 1] != ' ')
		{
			len = *i - start;
			if (len > 0)
				new_ret = ft_strjoin_free(new_ret, ft_substr(str, start, len));
			new_ret = handle_dollar(new_ret, str, i, env);
			start = *i;
		}
		else
			(*i)++;
	}
	len = *i - start;
	if (len > 0)
		new_ret = ft_strjoin_free(new_ret, ft_substr(str, start, len));
	*i += (str[*i] == '\n');
	return (free(ret), new_ret);
}

char	*handle_dilim(char *ret, char *str, size_t *i)
{
	size_t	start;
	char	*substr;
	char	*new_ret;

	if (*str == '$' && (*(str + 1) == '\'' || *(str + 1) == '\"'))
		(*i)++;
	start = *i;
	while (str[*i])
		(*i)++;
	substr = ft_substr(str, start, *i - start);
	if (!substr)
		return (NULL);
	new_ret = ft_strjoin_free(ret, substr);
	if (!new_ret)
		return (NULL);
	return (new_ret);
}
