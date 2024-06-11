/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 00:22:45 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/05 00:23:52 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_lstclear(t_env **lst, void (*del)(void *))
{
	t_env	*current;
	t_env	*tmp;

	if (*lst == NULL || del == NULL)
		return ;
	current = *lst;
	while (current)
	{
		tmp = current;
		current = current->next;
		del(tmp->env);
		free(tmp);
	}
	*lst = NULL;
}
