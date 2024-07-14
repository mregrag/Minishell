/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:49:44 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/11 19:29:46 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void	cd_err(t_env *env)
{
	ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
	ft_putstr_fd("cannot access parent directories: ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
	set_env_var(env, "?", "1");
}

static	char	*home(t_env *env)
{
	char	*path;

	path = get_env_var(env, "HOME");
	if (!path)
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		exit_status(1, env);
		return (NULL);
	}
	return (path);
}

static int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

int	ft_cd(t_node *node, t_env *env)
{
	char	s[PATH_MAX];
	char	new[PATH_MAX];
	char	*path;
	char	*old_pwd;

	if (!node->cmd[1])
		path = home(env);
	else
		path = node->cmd[1];
	if (!is_directory(path))
	{
		print_error("minish", "cd", strerror(errno), NULL);
		return (1);
	}
	old_pwd = getcwd(s, PATH_MAX);
	set_env_var(env, "OLDPWD", old_pwd);
	if (chdir(path) < 0)
		return (1);
	path = getcwd(new, PATH_MAX);
	set_env_var(env, "PWD", path);
	if (!path)
		return (cd_err(env), 1);
	exit_status(0, env);
	return (1);
}
