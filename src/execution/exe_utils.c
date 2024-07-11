/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:11:01 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/11 02:58:08 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		print_error("minish", "fork", strerror(errno), NULL);
	return (pid);
}

int	ft_open(const char *pathname, int flags, mode_t mode)
{
	int	fd;

	fd = open(pathname, flags, mode);
	if (fd == -1)
		print_error("minish", (char *)pathname, strerror(errno), NULL);
	return (fd);
}

int	ft_pipe(int pipefd[2])
{
	int	result;

	result = pipe(pipefd);
	if (result == -1)
		print_error("minish", "pipe", strerror(errno), NULL);
	return (result);
}

int	ft_dup2(int oldfd, int newfd)
{
	int	result;

	result = dup2(oldfd, newfd);
	if (result == -1)
		print_error("minish", "dup2", strerror(errno), NULL);
	return (result);
}

int	ft_dup(int oldfd)
{
	int	newfd;

	newfd = dup(oldfd);
	if (newfd == -1)
		print_error("minish", "dup", strerror(errno), NULL);
	return (newfd);
}
