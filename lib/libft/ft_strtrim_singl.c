/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_singl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 08:32:11 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/15 08:32:41 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strtrim_single(char const *s1, char const *set)
{
	size_t start;
	size_t end;
	char *str;

	if (!s1 || !set)
		return (NULL);

	end = ft_strlen(s1);
	start = 0;

	if (s1[start] && ft_strchr(set, s1[start]))
		start++;
	if (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + start, end - start + 1);
	return (str);
}
