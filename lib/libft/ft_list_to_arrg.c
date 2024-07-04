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

char **ft_list_to_arr(t_list *lst)
{
    char **strs;
    int i;
    int len;

    i = 0;
    len = ft_lstsize(lst);
    strs = ft_calloc(len + 1, sizeof(char *));
    if (!strs)
        return (NULL); // Return NULL if allocation fails
    while (i < len)
    {
        strs[i++] = ft_strdup((char *)lst->content); // Duplicate strings
        if (!strs[i - 1])
        {
            ft_free_array(strs); // Free previously allocated strings if duplication fails
            return (NULL);
        }
        lst = lst->next;
    }
    return (strs);
}