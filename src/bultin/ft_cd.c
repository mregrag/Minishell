/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:49:44 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/06 23:19:29 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_dir(char **argv)
{
	char	*pwd;

	pwd = NULL;
	if (!argv[1])
	{
		pwd = ft_getenv("HOME");
		if (!pwd)
			print_error("minish", "cd", NULL, "HOME not set");
	}
	else if (argv[1] && ft_strncmp(argv[1], "-", 2) == 0)
	{
		pwd = ft_getenv("OLDPWD");
		if (!pwd)
			print_error("minish", "cd", NULL, "OLDPWD not set");
	}
	else
		pwd = argv[1];
	return (pwd);
}

static int	update_pwd(void)
{
	char	buf[PATH_MAX];
	char	*pwd;

	pwd = ft_getenv("PWD");

	if (ft_getenv("PWD") && !is_env_var("OLDPWD", minish.env))
		create_env_var(ft_strjoin(ft_strjoin("OLDPWD", "="), pwd), &minish.env);
	update_env_var("OLDPWD", pwd, minish.env);
	if (!getcwd(buf, sizeof(buf)))
	{
		print_error_errno("cd", "error retrieving current directory",\
				"getcwd :  cannot access parent directories");
		return (1);
	}
	update_env_var("PWD", buf, minish.env);
		return (1);
	return (0);
}

int	ft_cd(char **argv)
{
	char	*pwd;

	pwd = get_dir(argv);
	if (!pwd)
		return (EXIT_FAILURE);
	if (chdir(pwd) == -1)
	{
		print_error_errno("minish", "cd", pwd);
		return (EXIT_FAILURE);
	}
	if (argv[1] && !ft_strcmp(argv[1], "-"))
		printf("%s\n", pwd);
	if (update_pwd() == 1)
		return (EXIT_FAILURE);
	return (0);
}
