/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:14:54 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/29 17:25:37 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_char(char *s, char c)
{
	char	*result;

	result = malloc(ft_strlen(s) + 2);
	if (!result)
		return (NULL);
	ft_strcpy(result, s);
	result[ft_strlen(s)] = c;
	result[ft_strlen(s) + 1] = '\0';
	ft_free(s);
	return (result);
}
