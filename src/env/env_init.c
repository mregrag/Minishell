/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:22:51 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/25 17:17:04 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_env_var(char *var, t_list *env)
{
	int		i;
	char	*envstr;

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

void	increment_shlvl(void)
{
	char	*val;

	if (!is_env_var("SHLVL", g_minish.env))
		create_env_var("SHLVL=1", &g_minish.env);
	else
	{
		val = ft_itoa(ft_atoi(ft_getenv("SHLVL")) + 1);
		update_env_var("SHLVL", val, g_minish.env);
		free(val);
	}
}

void	duplicate_env(t_list **env, char **envp)
{
	char	*tmp;
	char	buf[PATH_MAX];

	getcwd(buf, sizeof(buf));
	if (!envp || !*envp)
	{
		g_minish.dpath = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		create_env_var("_", &g_minish.env);
		increment_shlvl();
		create_env_var(ft_strjoin(ft_strjoin("PWD", "="), buf), &g_minish.env);
		create_env_var(ft_strjoin(ft_strjoin("PATH", "="), g_minish.dpath), &g_minish.env);
	}
	while (*envp)
	{
		tmp = ft_strdup(*envp);
		if (!tmp)
			exit(EXIT_FAILURE);
		ft_lstadd_back(env, ft_lstnew(tmp));
		envp++;
	}
}

void	init_minishell(t_gb *g_minish, char **envp)
{
	ft_bzero(g_minish, sizeof(t_gb));
	duplicate_env(&g_minish->env, envp);
	increment_shlvl();
}
