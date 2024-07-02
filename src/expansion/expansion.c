/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:10:09 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/02 00:15:25 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expansion_input(char *str, t_node *node)
{
	size_t	i;
	char	*ret;
	char	*result;

	ret = strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			ret = handle_single_quotes(ret, str, &i);
		else if (str[i] == '"')
			ret = handle_double_quotes(ret, str, &i, node);
		else if (str[i] == '$')
			ret = handle_dollar(ret, str, &i, node);
		else
			ret = handle_normal(ret, str, &i);
	}
	result = remov_quotes(ret);
	return (result);
}

char	*expansion_content(char *str, t_node *node)
{
	size_t	i;
	char	*ret;

	ret = strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			ret = handle_quotes(ret, str, &i, node);
		else if (str[i] == '$')
			ret = handle_dollar(ret, str, &i, node);
		else
			ret = handle_normal(ret, str, &i);
	}
	return (ret);
}

char	*expansion_dilim(char *str, t_node *node)
{
	size_t	i;
	char	*ret;

	ret = strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			node->flag = 1;
			ret = handle_quotes_dilim(ret, str, &i);
		}
		else
			ret = handle_str(ret, str, &i);
	}
	return (remov_quotes(ret));
}
