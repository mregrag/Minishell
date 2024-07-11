/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:16:01 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/11 06:27:34 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	increment_shlvl(t_env *env)
{
	char	*shlvl_str;
	int		shlvl;

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

int	is_var_in_env(t_env *env, const char *var_name)
{
	t_list	*current;
	size_t	var_len;

	if (!env || !var_name)
		return (0);
	var_len = ft_strlen(var_name);
	current = env->env;
	while (current)
	{
		if (ft_strncmp(current->content, var_name, var_len) == 0
			&& ((char *)current->content)[var_len] == '=')
			return (1);
		current = current->next;
	}
	return (0);
}

void	init_env(t_env **env, char **envp)
{
	char	*tmp;
	char	cwd[PATH_MAX];

	if (!env || !envp)
		return ;
	*env = malloc(sizeof(t_env));
	if (!*env)
		malloc_error();
	(*env)->env = NULL;
	while (*envp)
	{
		tmp = ft_strdup(*envp);
		if (!tmp)
			malloc_error();
		ft_lstadd_back(&((*env)->env), ft_lstnew(tmp));
		envp++;
	}
	set_env_var(*env, "?", "0");
	if (!is_var_in_env(*env, "PWD"))
		if (getcwd(cwd, sizeof(cwd)))
			set_env_var(*env, "PWD", cwd);
	if (!is_var_in_env(*env, "PATH"))
		set_env_var(*env, "PATH", "/usr/local/bin:/usr/bin:/bin");
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
		if (content[0] != '?' || content[1] != '=')
			ft_putendl_fd(content, 1);
		current = current->next;
	}
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
