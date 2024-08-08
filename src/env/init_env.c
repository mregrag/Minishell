/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:16:01 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/08 15:39:13 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	increment_shlvl(t_env *env)
{
	char	*shlvl_str;
	int		shlvl;

	shlvl_str = get_env_var(env, "SHLVL");
	if (!shlvl_str)
		shlvl = 1;
	else
	{
		shlvl = ft_atoi(shlvl_str);
		if (shlvl == -1)
			shlvl++;
		free(shlvl_str);
	}
	shlvl++;
	shlvl_str = ft_itoa(shlvl);
	if (shlvl_str)
		(set_env_var(env, "SHLVL", shlvl_str), free(shlvl_str));
}

void	initialize_enviroment(t_env **env, char **envp)
{
	char	cwd[PATH_MAX];

	if (!env || !envp)
		return ;
	*env = ft_calloc(sizeof(t_env), 1);
	if (!*env)
		malloc_error();
	while (*envp)
	{
		if (!ft_strncmp(*envp, "OLDPWD", 6))
		{
			set_env_var(*env, "OLDPWD", NULL);
			envp++;
		}
		ft_lstadd_back(&((*env)->env), ft_lstnew(ft_strdup(*envp)));
		envp++;
	}
	set_env_var(*env, "?", "0");
	if (!is_var_in_env(*env, "PWD"))
		set_env_var(*env, "PWD", getcwd(cwd, sizeof(cwd)));
	if (!is_var_in_env(*env, "PATH"))
		set_env_var(*env, "PATH", "/usr/local/bin:/usr/bin:/bin:.");
	increment_shlvl(*env);
}

void	print_env(t_env *env)
{
	t_list	*current;
	char	*content;

	if (!env)
		return ;
	current = env->env;
	while (current)
	{
		content = (char *)current->content;
		if (content[0] != '?' && ft_strchr(content, '='))
			ft_putendl_fd(content, 1);
		current = current->next;
	}
}
