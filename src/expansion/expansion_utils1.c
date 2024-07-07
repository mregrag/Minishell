/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:51:41 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/07 23:12:14 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_quotes(char *ret, char *str, size_t *i, t_env *env)
{
	char	*new_ret;
	char	*temp;
	char	current[2];

	new_ret = ft_strdup(ret);
	current[1] = '\0';
	while (str[*i] && str[*i] != '\n')
	{
		if (str[*i] == '$' && str[*i + 1] && str[*i + 1] != ' ')
		{
			temp = handle_dollar(new_ret, str, i, env);
			new_ret = temp;
		}
		else
		{
			current[0] = str[*i];
			temp = ft_strjoin(new_ret, current);
			free(new_ret);
			new_ret = temp;
			(*i)++;
		}
	}
	if (str[*i] == '\n')
		(*i)++;
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
