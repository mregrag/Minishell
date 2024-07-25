/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:26:45 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/24 17:37:27 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	long	result;
	long	new;
	int		sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		new = result * 10 + (*str - 48);
		if ((new < result && sign == 1) || (result > 0 && new == LONG_MAX))
			return (LONG_MAX);
		if ((new < result && sign == -1) || (result > 0 && new == LONG_MAX))
			return (LONG_MIN);
		result = new;
		str++;
	}
	return (sign * result);
}
