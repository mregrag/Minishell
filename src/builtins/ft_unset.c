/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:51:07 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/23 16:05:38 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	delete_env_var(t_list **head, char *var)
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

int	check_var_unset(char *var)
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

int	ft_unset(char **args)
{
	while (*(++args))
	{
		if (!check_var_unset(*args))
			return (0);
		delete_env_var(&minish.env, *args);
	}
	return (1);
}
