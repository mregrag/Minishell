/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:10:09 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/13 20:38:10 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expansion_input(char *str, t_env *env)
{
	char	*ret;

	ret = ft_strdup("");
	if (!ret)
		malloc_error();
	while (*str)
	{
		if (*str == '\'')
			ret = handle_single_quotes(ret, &str);
		else if (*str == '"')
			ret = handle_double_quotes(ret, &str, env);
		else if (*str == '$')
			ret = handle_dollar(ret, &str, 0, env);
		else
			ret = handle_normal(ret, &str);
	}
	if (ft_is_empty_string(ret))
		return (free(ret), NULL);
	return (handle_final_case(ret));
}

char	*expansion_content(char *str, t_env *env)
{
	size_t	i;
	char	*ret;

	i = 0;
	ret = strdup("");
	if (!ret)
		malloc_error();
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			ret = handle_quotes(ret, &str, env);
		else if (str[i] == '$')
			ret = handle_dollar(ret, &str, 1, env);
		else
			ret = handle_normal(ret, &str);
	}
	return (ret);
}

char	*expansion_dilim(char *str)
{
	size_t	i;
	char	*ret;

	ret = strdup("");
	if (!ret)
		malloc_error();
	i = 0;
	while (str[i])
		ret = handle_str(ret, str, &i);
	return (handle_final_case(ret));
}
