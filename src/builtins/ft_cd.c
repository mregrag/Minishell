/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:49:44 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/22 18:43:15 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void	cd_err(void)
{
	ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
	ft_putstr_fd("cannot access parent directories: ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
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

static int	change_directory(char *path, t_env *env, char *old_pwd)
{
	char	new[PATH_MAX];
	char	*new_pwd;

	if (chdir(path) < 0)
		return (1);
	new_pwd = getcwd(new, PATH_MAX);
	if (!new_pwd)
		return (cd_err(), 1);
	set_env_var(env, "OLDPWD", old_pwd);
	set_env_var(env, "PWD", new_pwd);
	exit_status(0, env);
	return (1);
}

int	ft_cd(t_node *node, t_env *env)
{
	char	old[PATH_MAX];
	char	*path;
	char	*allocated_path;
	char	*old_pwd;

	path = NULL;
	allocated_path = NULL;
	old_pwd = getcwd(old, PATH_MAX);
	if (!node->cmd[1])
	{
		allocated_path = home(env);
		if (!allocated_path)
			return (1);
		path = allocated_path;
	}
	else
		path = node->cmd[1];
	if (!is_directory(path))
	{
		print_error("minish", "cd", strerror(errno), NULL);
		return ((exit_status(1, env), free(allocated_path)), 1);
	}
	if (change_directory(path, env, old_pwd))
		return (free(allocated_path), 1);
	return (free(allocated_path), 1);
}
