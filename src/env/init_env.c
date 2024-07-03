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
bool is_var_in_env(t_env *env, const char *var_name)
{
    t_list *current;
    size_t var_len;

    if (!env || !var_name)
        return false;

    var_len = strlen(var_name);
    current = env->env;

    while (current)
    {
        if (strncmp(current->content, var_name, var_len) == 0 &&
            ((char *)current->content)[var_len] == '=')
        {
            return true;
        }
        current = current->next;
    }

    return false;
}

void    init_env(t_env *env, char **envp)
{
    char    *tmp;
    char    cwd[PATH_MAX];

    if (!env || !envp)
        return;

    env->env = NULL;
    while (*envp)
    {
        tmp = ft_strdup(*envp);
        if (!tmp)
        {
            free_env(env);
            return;
        }
        ft_lstadd_back(&(env->env), ft_lstnew(tmp));
        envp++;
    }
    increment_shlvl(env);
    set_env_var(env, "?", "0");
    if (!is_var_in_env(env, "PWD"))
        if (getcwd(cwd, sizeof(cwd)))
            set_env_var(env, "PWD", cwd);
    if (!is_var_in_env(env, "PATH"))
        set_env_var(env, "PATH", "/usr/local/bin:/usr/bin:/bin");
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
