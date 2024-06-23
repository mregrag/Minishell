/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issamechar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:24:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/23 16:24:59 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_issamechar(char *str, int c)
{
	size_t	count;
	int		i;

	i = 0;
	count = 0;
	while (str[i])
		if (str[i++] == c)
			count++;
	return (ft_strlen(str) == count);
}
