/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 18:33:04 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/01 21:47:35 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_status(int status, t_node *node)
{
	set_env_var(node->env, "?", ft_itoa(status));
}

int	exec_err(int err, char *path, char *cmd)
{
	struct stat	f_stat;
	(void)err;

	stat(path, &f_stat);
	if (S_ISDIR(f_stat.st_mode))
		return (print_error("minish", cmd, "is a directory", NULL), 126);
	if (ft_strchr(cmd, '/') && access(cmd, F_OK))
		return (print_error("minish", cmd, "No such file or directory", NULL), 127);
	else if (!access(path, F_OK) && access(path, X_OK))
		return (print_error("minish", "Permission denied", path, NULL), 126);
	else if (!path)
		return (print_error("minish", "No such file or directory", path, NULL), 127);
	else
		return (print_error("minish",cmd, "command not found", NULL), 127);
	return (1);
}
int	print_error(char *s1, char *s2, char *s3, char *message)
{
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
	{
		if (s1)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s2, 2);
	}
	if (s3)
	{
		if (s1 || s2)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s3, 2);
	}
	if (message)
	{
		if (s1 || s2 || s3)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(message, 2);
	}
	ft_putchar_fd('\n', 2);
	return (1);
}

int	print_error_errno(char *s1, char *s2, char *s3)
{
	print_error(s1, s2, s3, strerror(errno));
	errno = 0;
	return (1);
}
