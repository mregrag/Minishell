/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:51:07 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/26 16:43:15 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	delete_env_var(t_list **head, char *var)
{
	t_list	*temp;
	t_list	*prev;

	temp = *head;
	if (temp && !ft_strncmp(temp->content, var, ft_strlen(var)))
	{
		*head = temp->next;
		free(temp);
		temp = NULL;
		return ;
	}
	while (temp && ft_strncmp(temp->content, var, ft_strlen(var)))
	{
		prev = temp;
		temp = temp->next;
	}
	if (!temp)
		return ;
	prev->next = temp->next;
	free(temp);
	temp = NULL;
}

static int	check_var_unset(char *var)
{
	if (!var || ft_strchr(var, '_'))
		return (0);
	if (ft_strchr(var, '=') || ft_strchr(var, '\'') || ft_strchr(var, '"')
		|| ft_strchr(var, '$') || *var == '/' || ft_isdigit(*var))
	{
		print_error("minish", "unset", var, "not a valid identifier");
		return (0);
	}
	return (1);
}

int	ft_unset(t_node *node)
{
	while (*(++node->cmd))
	{
		if (!check_var_unset(*node->cmd))
			return (0);
		delete_env_var(&node->env, *node->cmd);
	}
	return (1);
}
