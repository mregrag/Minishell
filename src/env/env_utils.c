/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:25:14 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/13 00:03:22 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_var(t_env *env, char *var)
{
	t_list	*current;
	char	*tmp;
	size_t	len;

	if (!env || !var)
		return (NULL);
	len = ft_strlen(var);
	current = env->env;
	while (current)
	{
		tmp = (char *)current->content;
		if (ft_strncmp(tmp, var, len) == 0 && tmp[len] == '=')
			return (ft_strdup(tmp + len + 1));
		current = current->next;
	}
	return (NULL);
}

void	set_env_var(t_env *env, char *var, char *value)
{
	t_list	*current;
	char	*new_var;
	size_t	len;

	if (!env || !var || !value)
		return ;
	len = ft_strlen(var);
	new_var = ft_strjoin_three(var, "=", value);
	if (!new_var)
		return ;
	current = env->env;
	while (current)
	{
		if (ft_strncmp(current->content, var, len) == 0)
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

void	unset_env_var(t_env *env, char *var)
{
	t_list	*current;
	t_list	*prev;
	size_t	len;

	if (!env || !var)
		return ;
	len = ft_strlen(var);
	current = env->env;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->content, var, len) == 0)
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

void	append_env_var(t_env *env, char *var, char *value)
{
	t_list	*current;
	char	*old_value;
	char	*new_value;
	char	*new_var;
	size_t	len;

	if (!env || !var || !value)
		return ;
	len = ft_strlen(var);
	current = env->env;
	while (current)
	{
		if (ft_strncmp(current->content, var, len) == 0)
		{
			old_value = ft_strchr(current->content, '=') + 1;
			new_value = ft_strjoin(old_value, value);
			new_var = ft_strjoin_three(var, "=", new_value);
			free(current->content);
			current->content = new_var;
			free(new_value);
			return ;
		}
		current = current->next;
	}
	set_env_var(env, var, value);
}
