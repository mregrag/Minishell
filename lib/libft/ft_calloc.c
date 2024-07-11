/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:37:24 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/11 06:31:31 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp;
	size_t	total;

	total = count * size;
	if (count != 0 && total / count != size)
		return (NULL);
	tmp = malloc(total);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, total);
	return (tmp);
}
