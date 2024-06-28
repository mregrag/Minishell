/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:25:14 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/28 14:37:40 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_getenv(const char *key, t_list *env)
{
	int		i;
	t_list	*envp;
	char	*tmp;
	char	*value;

	envp = env;
	if (!key)
		return (NULL);
	while (envp)
	{
		i = 0;
		tmp = (char *)envp->content;
		while (key[i] && tmp[i] && (key[i] == tmp[i]))
			i++;
		if (!key[i] && (tmp[i] == '=' || tmp[i] == '\0'))
		{
			value = ft_strdup(&(tmp[i + 1]));
			if (!value)
				return (NULL);
			return (value);
		}
		envp = envp->next;
	}
	return (NULL);
}

void	update_env_var(char *var, char *value, t_node *node)
{
	t_list	*current;
	char	*new_entry;
	char	*var_with_equals;

	var_with_equals = ft_strjoin(var, "=");
	if (!var_with_equals)
		return ;
	new_entry = ft_strjoin(var_with_equals, value);
	free(var_with_equals);
	if (!new_entry)
		return ;
	current = node->env;
	while (current)
	{
		if (ft_strncmp(current->content, var, ft_strlen(var)) == 0
				&& ((char *)current->content)[ft_strlen(var)] == '=')
		{
			free(current->content);
			current->content = ft_strdup(new_entry);
			free(new_entry);
			return ;
		}
		current = current->next;
	}
	ft_lstadd_back(&node->env, ft_lstnew(ft_strdup(new_entry)));
	free(new_entry);
}
