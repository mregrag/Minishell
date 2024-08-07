/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 00:01:52 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/06 21:41:15 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_std_fds(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
}

void	get_std_fds(int *in_out)
{
	in_out[0] = dup(STDIN_FILENO);
	in_out[1] = dup(STDOUT_FILENO);
}

int	is_var_in_env(t_env *env, char *var_name)
{
	if (!env || !var_name)
		return (0);
	return (find_env_var(env, var_name) != NULL);
}

t_list	*find_env_var(t_env *env, char *var)
{
	t_list	*current_node;
	size_t	var_len;

	current_node = env->env;
	var_len = ft_strlen(var);
	while (current_node)
	{
		if (ft_strncmp(current_node->content, var, var_len) == 0
			&& (((char *)current_node->content)[var_len] == '='
			|| ((char *)current_node->content)[var_len] == '\0'))
			return (current_node);
		current_node = current_node->next;
	}
	return (NULL);
}

void	free_env(t_env *env)
{
	t_list	*current;
	t_list	*next;

	if (!env)
		return ;
	current = env->env;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	free(env);
	rl_clear_history();
}
