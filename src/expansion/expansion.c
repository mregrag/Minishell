/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:10:09 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/23 12:50:59 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expansion_input(char *str, t_env *env)
{
	size_t	i;
	char	*ret;
	char	*temp;

	i = 0;
	while (str[i])
	{
		temp = ret;
		if (str[i] == '\'')
			ret = handle_single_quotes(ret, str, &i);
		else if (str[i] == '"')
			ret = handle_double_quotes(ret, str, &i, env);
		else if (str[i] == '$')
			ret = handle_dollar(ret, str, &i, env);
		else
			ret = handle_normal(ret, str, &i);
		if (!ret)
			return (free(temp), NULL);
	}
	return (handle_final_case(ret));
}

char	*expansion_content(char *str, t_env *env)
{
	size_t	i;
	char	*ret;
	char	*temp;

	i = 0;
	ret = strdup("");
	if (!ret)
		return (NULL);
	while (str[i])
	{
		temp = ret;
		if (str[i] == '\'' || str[i] == '"')
			ret = handle_quotes(ret, str, &i, env);
		else if (str[i] == '$')
			ret = handle_dollar(ret, str, &i, env);
		else
			ret = handle_normal(ret, str, &i);
		if (!ret)
			return (free(temp), NULL);
	}
	return (ret);
}

char	*expansion_dilim(char *str)
{
	size_t	i;
	char	*ret;

	ret = strdup("");
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i])
		ret = handle_str(ret, str, &i);
	return (handle_final_case(ret));
}
