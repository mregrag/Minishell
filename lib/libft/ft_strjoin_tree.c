/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 05:48:14 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/01 15:41:19 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3)
{
	char	*result;
	int		i;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	if (!s1 && !s2 && !s3)
		return (NULL);
	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	result = malloc(sizeof(char) * (len1 + len2 + len3 + 1));
	if (!result)
		return (NULL);
	while (*s1)
		result[i++] = *s1++;
	while (*s2)
		result[i++] = *s2++;
	while (*s3)
		result[i++] = *s3++;
	result[i] = '\0';
	return (result);
}
