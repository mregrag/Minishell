/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:42:40 by mregrag           #+#    #+#             */
/*   Updated: 2024/05/02 18:43:05 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_atoi(const char *str)
{
	long	result;
	long	new_result;
	int		sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			sign *= -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		new_result = result * 10 + (*str - 48);
		if (new_result < result && sign == 1)
			return (-1);
		if (new_result < result && sign == -1)
			return (0);
		str++;
		result = new_result;
	}
	return (result * sign);
}
