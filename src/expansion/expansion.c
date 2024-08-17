/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:10:09 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/16 22:59:11 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_variable(char *str, int flag, t_env *env)
{
	size_t	i;
	char	*ret;

	ret = ft_strdup("");
	if (!ret)
		malloc_error();
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			ret = handle_single_quotes(ret, str, &i);
		else if (str[i] == '"')
			ret = handle_double_quotes(ret, str, &i, env);
		else if (str[i] == '$' && flag)
			ret = handle_dilim(ret, str, &i);
		else if (str[i] == '$')
			ret = handle_dollar(ret, str, &i, env);
		else
			ret = handle_normal(ret, str, &i);
		if (!ret)
			return (NULL);
	}
	return (ret);
}

char	*expand_export(char *str, int flag, t_env *env)
{
	size_t	i;
	char	*ret;

	ret = ft_strdup("");
	if (!ret)
		malloc_error();
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			ret = handle_single_quotes(ret, str, &i);
		else if (str[i] == '"')
			ret = handle_double_quotes(ret, str, &i, env);
		else if (str[i] == '$' && flag)
			ret = handle_dilim(ret, str, &i);
		else if (str[i] == '$')
			ret = handle_dollar_export(ret, str, &i, env);
		else
			ret = handle_normal(ret, str, &i);
		if (!ret)
			return (NULL);
	}
	return (ret);
}

char	*expand_content(char *str, t_env *env)
{
	size_t	i;
	char	*ret;
	char	*temp;

	i = 0;
	ret = strdup("");
	if (!ret)
		malloc_error();
	while (str[i])
	{
		temp = ret;
		if (str[i] == '\'' || str[i] == '"')
			ret = handle_quotes(ret, str, &i, env);
		else if (str[i] == '$')
			ret = handle_dollar_her(ret, str, &i, env);
		else
			ret = handle_normal(ret, str, &i);
		if (!ret)
			return (free(temp), NULL);
	}
	return (ret);
}
