/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:25:14 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/05 15:17:54 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_env_var(char *var, char *value, t_node *node)
{
	t_list	*current;
	char	*new_entry;

	new_entry = ft_strjoin(ft_strjoin(var, "="), value);
	if (!new_entry)
		return ;
	current = node->env->env;
	while (current)
	{
		if (ft_strncmp(current->content, var, ft_strlen(var)) == 0
				&& ((char *)current->content)[ft_strlen(var)] == '=')
		{
			current->content = ft_strdup(new_entry);
			ft_free(&new_entry);
			return ;
		}
		current = current->next;
	}
	ft_lstadd_back(&node->env->env, ft_lstnew(ft_strdup(new_entry)));
	free(new_entry);
}

char	*get_env_var(t_env *env, const char *name)
{
	t_list	*current;
	char	*tmp;
	size_t	len;

	if (!env || !name)
		return (NULL);
	len = ft_strlen(name);
	current = env->env;
	while (current)
	{
		tmp = (char *)current->content;
		if (ft_strncmp(tmp, name, len) == 0 && tmp[len] == '=')
			return (ft_strdup(tmp + len + 1));
		current = current->next;
	}
	return (NULL);
}

int	set_env_var(t_env *env, const char *name, const char *value)
{
	t_list	*current;
	char	*new_var;
	size_t	len;

	if (!env || !name || !value)
		return (-1);
	len = ft_strlen(name);
	new_var = ft_strjoin_three(name, "=", value);
	if (!new_var)
		return (-1);
	current = env->env;
	while (current)
	{
		if (ft_strncmp(current->content, name, len) == 0 && ((char *)current->content)[len] == '=')
		{
			free(current->content);
			current->content = new_var;
			return (0);
		}
		current = current->next;
	}
	ft_lstadd_back(&(env->env), ft_lstnew(ft_strdup(new_var)));
	free(new_var);
	return (0);
}

int	unset_env_var(t_env *env, const char *name)
{
	t_list	*current;
	t_list	*prev;
	size_t	len;

	if (!env || !name)
		return (-1);
	len = ft_strlen(name);
	current = env->env;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->content, name, len) == 0 && ((char *)current->content)[len] == '=')
		{
			if (prev)
				prev->next = current->next;
			else
				env->env = current->next;
			free(current->content);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (-1);
}
