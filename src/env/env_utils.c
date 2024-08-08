/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:25:14 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/08 15:41:26 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_var(t_env *env, char *var)
{
	t_list	*var_node;
	char	*content;
	char	*value;
	size_t	var_len;

	if (!env || !var)
		return (NULL);
	var_node = find_env_var(env, var);
	if (!var_node)
		return (NULL);
	content = (char *)var_node->content;
	var_len = ft_strlen(var);
	if (content[var_len] != '=')
		return (NULL);
	value = ft_strdup(content + var_len + 1);
	if (!value)
		malloc_error();
	return (value);
}

char	*get_env_var_dollar(t_env *env, char *var)
{
	t_list	*var_node;
	char	*content;
	char	*value;
	size_t	var_len;

	if (!env || !var)
		return (NULL);
	var_node = find_env_var(env, var);
	if (!var_node)
		return (NULL);
	content = (char *)var_node->content;
	var_len = ft_strlen(var);
	if (content[var_len] != '=')
		return (NULL);
	value = ft_strjoin_three("\"", content + var_len + 1, "\"");
	if (!value)
		malloc_error();
	return (value);
}

void	set_env_var(t_env *env, char *var, char *value)
{
	t_list	*existing_var;
	char	*new_var;

	if (!env || !var)
		return ;
	if (value)
		new_var = ft_strjoin_three(var, "=", value);
	else
		new_var = ft_strdup(var);
	if (!new_var)
		malloc_error();
	existing_var = find_env_var(env, var);
	if (existing_var)
	{
		free(existing_var->content);
		existing_var->content = new_var;
	}
	else
		ft_lstadd_back(&(env->env), ft_lstnew(new_var));
}

void	unset_env_var(t_env *env, char *var)
{
	t_list	*current_node;
	t_list	*prev_node;

	if (!env || !var)
		return ;
	current_node = env->env;
	prev_node = NULL;
	while (current_node)
	{
		if (current_node == find_env_var(env, var))
		{
			if (prev_node)
				prev_node->next = current_node->next;
			else
				env->env = current_node->next;
			free(current_node->content);
			free(current_node);
			return ;
		}
		prev_node = current_node;
		current_node = current_node->next;
	}
}

void	append_env_var(t_env *env, char *var, char *value)
{
	t_list	*current_node;
	char	*old_value;
	char	*new_value;
	char	*new_content;

	if (!env || !var || !value)
		return ;
	current_node = find_env_var(env, var);
	if (current_node)
	{
		old_value = ft_strchr(current_node->content, '=');
		if (old_value)
			new_value = ft_strjoin(old_value + 1, value);
		else
			new_value = ft_strdup(value);
		new_content = ft_strjoin_three(var, "=", new_value);
		if (!new_content)
			return (free(new_value));
		free(current_node->content);
		current_node->content = new_content;
		free(new_value);
	}
	else
		set_env_var(env, var, value);
}
