/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:22:51 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/26 23:34:11 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_env_var(char *var, t_list *env)
{
	int		i;
	char	*envstr;

	if (!*var)
		return (0);

	while (env)
	{
		i = 0;
		envstr = (char *)env->content;
		while (var[i] && envstr[i] && (var[i] == envstr[i]))
			i++;
		if (!var[i] && (envstr[i] == '=' || !envstr[i]))
			return (1);
		env = env->next;
	}
	return (0);
}

void	create_env_var(char *var, t_list **env)
{
	t_list	*new_var;
	char	*new_var_str;

	new_var_str = ft_strdup(var);
	if (new_var_str == 0)
		exit(EXIT_FAILURE);
	new_var = ft_lstnew(new_var_str);
	if (new_var == 0)
		exit(EXIT_FAILURE);
	ft_lstadd_front(env, new_var);
}

void	increment_shlvl(t_node *node)
{
	char	*val;

	if (!is_env_var("SHLVL", node->env))
		create_env_var("SHLVL=1", &node->env);
	else
	{
		val = ft_itoa(ft_atoi(ft_getenv("SHLVL", node->env)) + 1);
		update_env_var("SHLVL", val, node->env);
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
		{
			tmp = ft_strjoin("PWD=", buf);
			ft_lstadd_back(&node->env, ft_lstnew(tmp));
		}
		ft_lstadd_back(&node->env, ft_lstnew(ft_strdup("SHLVL=0")));
		ft_lstadd_back(&node->env, ft_lstnew(ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.")));
		ft_lstadd_back(&node->env, ft_lstnew(ft_strdup("_")));
	}
	while (*env)
	{
		tmp = ft_strdup(*env);
		if (!tmp)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&node->env, ft_lstnew(tmp));
		env++;
	}
}

t_node	*init_minishell(char **env)
{
	t_node	*node;

	node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	duplicate_env(node, env);
	increment_shlvl(node);
	return (node);
}
