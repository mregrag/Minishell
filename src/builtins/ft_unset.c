/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:51:07 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/01 20:51:50 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	delete_env_var(t_list **head, char *var)
{
	t_list	*temp;
	t_list	*prev;
	int var_len = ft_strchr(var, '=') ? ft_strchr(var, '=') - var : ft_strlen(var);

	temp = *head;
	if (temp && !ft_strncmp(temp->content, var, var_len) &&
			(((char *)temp->content)[var_len] == '=' || ((char *)temp->content)[var_len] == '\0'))
	{
		*head = temp->next;
		free(temp->content);
		free(temp);
		return ;
	}

	while (temp && (ft_strncmp(temp->content, var, var_len) ||
				(((char *)temp->content)[var_len] != '=' && ((char *)temp->content)[var_len] != '\0')))
	{
		prev = temp;
		temp = temp->next;
	}

	if (!temp)
		return ;

	prev->next = temp->next;
	free(temp->content);
	free(temp);
}

static int	check_var_unset(char *var)
{
	int	i;

	i = 1;
	if (!var || *var == '\0')
		return (0);
	if (!ft_isalpha(*var) && *var != '_')
		return (0);
	while (var[++i])
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
	return (1);
}

int	ft_unset(t_node *node)
{
	char	**args;

	args = node->cmd;
	while (*(++args))
	{
		if (!check_var_unset(*args))
		{
			print_error("minishell", "unset", *args, "not a valid identifier");
			return (1);
		}
		else
			delete_env_var(&node->env->env, *args);
	}
	return (1);
}
