/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remov_quets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:09:36 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/24 16:35:48 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remov_quotes(char *str)
{
	char	*ret;
	char	quote;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ret = malloc(strlen(str) + 1);
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				ret[j++] = str[i++];
			i++;
		}
		else
			ret[j++] = str[i++];
	}
	ret[j] = '\0';
	(free(str), str = NULL);
	return (ret);
}
