/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issamechar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:26:58 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/02 18:50:07 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
