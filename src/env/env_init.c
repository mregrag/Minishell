/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:22:51 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/23 18:59:17 by mregrag          ###   ########.fr       */
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

void	create_env_var(char *token_str, t_list **env)
{
	t_list	*new_var;
	char	*new_var_str;

	new_var_str = ft_strdup(token_str);
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

	if (!is_env_var("SHLVL", minish.env))
		create_env_var("SHLVL=1", &minish.env);
	else
	{
		val = ft_itoa(ft_atoi(ft_getenv("SHLVL")) + 1);
		update_env_var("SHLVL", val, minish.env);
		free(val);
	}
}

void	duplicate_env(t_list **env, char **envp)
{
	char	*tmp;
	char	buf[PATH_MAX];

	getcwd(buf, sizeof(buf));
	// if (!envp || !*envp)
	// {
	// 	create_env_var("_", &minish.env);
	// 	increment_shlvl();
	// 	create_env_var(ft_strjoin(ft_strjoin("PWD", "="), buf), &minish.env);
	// 	minish.dpath = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	// }

	while (*envp)
	{
		tmp = ft_strdup(*envp);
		if (!tmp)
			exit(EXIT_FAILURE);
		ft_lstadd_back(env, ft_lstnew(tmp));
		envp++;
	}
}

static	void	duplicate_fd(void)
{
	minish.input = dup(STDIN_FILENO);
	minish.output = dup(STDOUT_FILENO);
}

void	set_fd(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}
void	init_minishell(t_gb *minish, char **envp)
{
	duplicate_fd();
	ft_bzero(minish, sizeof(t_gb));
	duplicate_env(&minish->env, envp);
	increment_shlvl();
}
