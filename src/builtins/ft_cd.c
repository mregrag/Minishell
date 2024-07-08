/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:49:44 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/08 19:56:56 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_dir(t_node *node, t_env *env)
{
	char	*pwd;

	pwd = NULL;
	if (!node->cmd[1])
	{
		pwd = get_env_var(env, "HOME");
		if (!pwd)
		{
			print_error("minish", "cd", NULL, "HOME not set");
			set_env_var(env, "?", "1");
		}
	}
	else if (node->cmd[1] && ft_strncmp(node->cmd[1], "-", 2) == 0)
	{
		pwd = get_env_var(env, "OLDPWD");
		if (!pwd)
		{
			print_error("minish", "cd", NULL, "OLDPWD not set");
			set_env_var(env, "?", "1");
		}
	}
	else
		pwd = node->cmd[1];
	return (pwd);
}

static int	update_pwd(t_env *env)
{
	char	buf[PATH_MAX];
	char	*pwd;

	pwd = get_env_var(env, "PWD");
	set_env_var(env, "OLDPWD", pwd);
	if (!getcwd(buf, sizeof(buf)))
	{
		print_error_errno("cd", "error retrieving current directory",\
				"getcwd :  cannot access parent directories");
		return (1);
	}
	set_env_var(env, "PWD", buf);
	if (!getcwd(buf, sizeof(buf)))
		return (1);
	return (0);
}

int	ft_cd(t_node *node, t_env *env)
{
	char	*pwd;

	pwd = get_dir(node, env);
	if (!pwd)
		return (EXIT_FAILURE);
	if (chdir(pwd) == -1)
	{
		print_error_errno("minish", "cd", pwd);
		return (EXIT_FAILURE);
	}
	if (node->cmd[1] && !ft_strcmp(node->cmd[1], "-"))
		printf("%s\n", pwd);
	if (update_pwd(env) == 1)
		return (1);
	return (1);
}

