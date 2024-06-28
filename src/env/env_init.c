/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:22:51 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/28 22:19:03 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <complex.h>
#include <unistd.h>

void	create_env_var(char *var, char *value, t_node *node)
{
	char	*tmp;
	char	*var_with_equals;

	var_with_equals = ft_strjoin(var, "=");
	if (!var_with_equals)
		return ;
	tmp = ft_strjoin(var_with_equals, value);
	free(var_with_equals);
	if (!tmp)
		return ;
	ft_lstadd_back(&node->env, ft_lstnew(ft_strdup(tmp)));
	free(tmp);
}

void	increment_shlvl(t_node *node)
{
	char	*val;

	if (!ft_getenv("SHLVL", node->env))
		create_env_var("SHLVL", "1",  node);
	else
	{
		val = ft_itoa(ft_atoi(ft_getenv("SHLVL", node->env)) + 1);
		update_env_var("SHLVL", val, node);
		free(val);
	}
}

void	duplicate_env(t_node *node, char **env)
{
	char	buf[PATH_MAX];
	char	*tmp;

	if (!env || !*env)
	{
		if (getcwd(buf, sizeof(buf)))
			create_env_var("PWD", buf, node);
		create_env_var("SHLVL", "0", node);
		create_env_var("PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", node);
		create_env_var("_", "", node);
	}
	while (*env)
	{
		tmp = ft_strdup(*env);
		if (!tmp)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&node->env, ft_lstnew(tmp));
		env++;
	}
	create_env_var("?", "0", node);
}

void	reset_in_out(int in, int out)
{
	ft_dup2(in, STDIN_FILENO);
	ft_dup2(out, STDOUT_FILENO);
}

t_node	*init_minishell(char **env, int *in, int *out)
{
	t_node	*node;

	node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	duplicate_env(node, env);
	increment_shlvl(node);
	*in = ft_dup(STDIN_FILENO);
	*out = ft_dup(STDOUT_FILENO);
	return (node);
}
