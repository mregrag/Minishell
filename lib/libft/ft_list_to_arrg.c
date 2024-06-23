/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_to_arrg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:28:12 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/23 16:28:49 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_list_to_arr(t_list *lst)
{
	char	**strs;
	int		i;
	int		len;

	i = 0;
	len = ft_lstsize(lst);
	strs = ft_calloc(len + 1, sizeof(char *));
	while (i < len)
	{
		strs[i++] = (char *)lst->content;
		lst = lst->next;
	}
	return (strs);
}
