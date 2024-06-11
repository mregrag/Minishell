/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remov_quets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:09:36 by mregrag           #+#    #+#             */
/*   Updated: 2024/05/28 16:20:01 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	ft_strlen_unquot(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			len++;
		i++;
	}
	return (len);
}

char	*remov_quotes(char *str)

{
	char	*ret;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ret = ft_calloc(1 + ft_strlen_unquot(str), sizeof(char));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			ret[j++] = str[i];
		i++;
	}
	return (free(str), str = NULL,  ret);
}

