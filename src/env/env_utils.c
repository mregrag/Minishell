/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:25:14 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/30 12:06:14 by mregrag          ###   ########.fr       */
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
	size_t	var_len;
	char	*new_var;
	char	*content;

	current = env->env;
	var_len = ft_strlen(var);
	if (value)
		new_var = ft_strjoin_three(var, "=", value);
	else
		new_var = ft_strdup(var);
	while (current)
	{
		content = (char *)current->content;
		if (!ft_strncmp(content, var, var_len)
			&& (content[var_len] == '=' || !content[var_len]))
		{
			free(current->content);
			current->content = new_var;
			return ;
		}
		current = current->next;
	}
	ft_lstadd_back(&(env->env), ft_lstnew(new_var));
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

static t_list	*find_env_var(t_env *env, char *var)
{
	t_list	*current;
	size_t	var_len;

	current = env->env;
	var_len = ft_strlen(var);
	while (current)
	{
		if (ft_strncmp(current->content, var, var_len) == 0
			&& (((char *)current->content)[var_len] == '='
			|| ((char *)current->content)[var_len] == '\0'))
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	append_env_var(t_env *env, char *var, char *value)
{
	t_list	*current;
	char	*old_value;
	char	*new_value;
	char	*new_content;

	if (!env || !var || !value)
		return ;
	current = find_env_var(env, var);
	if (current)
	{
		old_value = ft_strchr(current->content, '=');
		if (old_value)
			new_value = ft_strjoin(old_value + 1, value);
		else
			new_value = ft_strdup(value);
		new_content = ft_strjoin_three(var, "=", new_value);
		if (!new_content)
			return (free(new_value));
		free(current->content);
		current->content = new_content;
		free(new_value);
	}
	else
		set_env_var(env, var, value);
}
