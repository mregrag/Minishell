/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:20:09 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/11 06:28:19 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	char	*original_dst;

	original_dst = dst;
	if (!dst || !src)
		return (dst);
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return (original_dst);
}
