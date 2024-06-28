/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:49:44 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/28 22:53:36 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_dir(t_node *node)
{
	char	*pwd;

	pwd = NULL;
	if (!node->cmd[1])
	{
		pwd = ft_getenv("HOME", node->env);
		if (!pwd)
		{
			print_error("minish", "cd", NULL, "HOME not set");
			update_env_var("?", "1", node);
		}
	}
	else if (node->cmd[1] && ft_strncmp(node->cmd[1], "-", 2) == 0)
	{
		pwd = ft_getenv("OLDPWD", node->env);
		if (!pwd)
		{
			print_error("minish", "cd", NULL, "OLDPWD not set");
			update_env_var("?", "1", node);
		}
	}
	else
		pwd = node->cmd[1];
	return (pwd);
}

static int	update_pwd(t_node *node)
{
	char	buf[PATH_MAX];
	char	*pwd;

	pwd = ft_getenv("PWD", node->env);
	if (!ft_getenv("OLDPWD", node->env))
		create_env_var("OLDPWD", pwd, node);
	update_env_var("OLDPWD", pwd, node);
	if (!getcwd(buf, sizeof(buf)))
	{
		print_error_errno("cd", "error retrieving current directory",\
				"getcwd :  cannot access parent directories");
		return (1);
	}
	update_env_var("PWD", buf, node);
		return (1);
	return (0);
}

int	ft_cd(t_node *node)
{
	char	*pwd;

	pwd = get_dir(node);
	if (!pwd)
		return (EXIT_FAILURE);
	if (chdir(pwd) == -1)
	{
		print_error_errno("minish", "cd", pwd);
		return (EXIT_FAILURE);
	}
	if (node->cmd[1] && !ft_strcmp(node->cmd[1], "-"))
		printf("%s\n", pwd);
	if (update_pwd(node) == 1)
		return (EXIT_FAILURE);
	return (0);
}
