/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:16:01 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/01 23:09:12 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	increment_shlvl(t_env *env)
{
	char	*shlvl_str;
	int	shlvl;

	shlvl_str = get_env_var(env, "SHLVL");
	if (!shlvl_str)
		shlvl = 0;
	else
	{
		shlvl = ft_atoi(shlvl_str);
		free(shlvl_str);
	}
	shlvl++;
	shlvl_str = ft_itoa(shlvl);
	if (shlvl_str)
	{
		set_env_var(env, "SHLVL", shlvl_str);
		free(shlvl_str);
	}
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	char	*tmp;
	char	cwd[PATH_MAX];

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->env = NULL;
	while (*envp)
	{
		tmp = ft_strdup(*envp);
		if (!tmp)
		{
			free_env(env);
			return (free_env(env), NULL);
		}
		ft_lstadd_back(&(env->env), ft_lstnew(tmp));
		envp++;
	}
	increment_shlvl(env);
	set_env_var(env, "?", "1");
	if (!get_env_var(env, "PWD"))
		if (getcwd(cwd, sizeof(cwd)))
			set_env_var(env, "PWD", cwd);
	if (!get_env_var(env, "PATH"))
		set_env_var(env, "PATH", "/usr/local/bin:/usr/bin:/bin");
	return (env);
}

void	print_env(t_env *env)
{
	t_list	*current;

	if (!env)
		return ;
	current = env->env;
	while (current)
	{
		ft_putendl_fd((char *)current->content, STDOUT_FILENO);
		current = current->next;
	}
}

void	free_env(t_env *env)
{
	if (!env)
		return ;
	ft_lstclear(&(env->env), free);
	free(env);
}
