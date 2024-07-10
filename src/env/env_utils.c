/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:25:14 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/10 04:58:39 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_var(t_env *env, char *name)
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

void	set_env_var(t_env *env, char *name, char *value)
{
	t_list	*current;
	char	*new_var;
	size_t	len;

	if (!env || !name || !value)
		return ;
	len = ft_strlen(name);
	new_var = ft_strjoin_three(name, "=", value);
	if (!new_var)
		return ;
	current = env->env;
	while (current)
	{
		if (ft_strncmp(current->content, name, len) == 0
				&& ((char *)current->content)[len] == '=')
		{
			free(current->content);
			current->content = new_var;
			return ;
		}
		current = current->next;
	}
	ft_lstadd_back(&(env->env), ft_lstnew(ft_strdup(new_var)));
	free(new_var);
}

void	unset_env_var(t_env *env, char *name)
{
	t_list	*current;
	t_list	*prev;
	size_t	len;

	if (!env || !name)
		return ;
	len = ft_strlen(name);
	current = env->env;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->content, name, len) == 0
				&& ((char *)current->content)[len] == '=')
		{
			if (prev)
				prev->next = current->next;
			else
				env->env = current->next;
			free(current->content);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
