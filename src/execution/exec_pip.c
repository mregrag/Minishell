/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:43:10 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/13 00:20:52 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	pid_t	left_pipe(t_node *node, int fd[2])
{
	pid_t	pd;

	pd = fork();
	if (pd == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			return (-1);
		close(fd[0]);
		close(fd[1]);
		executing(node);
		exit(minish.exit_status);
	}
	return (pd);
}

static	pid_t	right_pipe(t_node *node, int fd[2])
{
	pid_t	pd;

	if (pd == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) < 0)
			return (-1);
		close(fd[1]);
		close(fd[0]);
		executing(node);
		exit(minish.exit_status);
	}
	return (pd);
}

void	exec_pipe(t_node *node)
{
	pid_t	pid_read;
	pid_t	pid_write;
	int		status;
	int		fd[2];

	if (pipe(fd) < 0)
		return ;
	pid_write = left_pipe(node->left, fd);
	if (pid_write < 0)
		return ;
	pid_read = right_pipe(node->right, fd);
	if (pid_read < 0)
		return ;
	close(fd[1]);
	close(fd[0]);
	waitpid(pid_read, &status, 0);
	waitpid(pid_write, &status, 0);
	exit_status(status);
}
