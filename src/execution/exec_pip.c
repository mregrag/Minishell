/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:43:10 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/03 22:11:57 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static pid_t	left_pipe(t_node *node, int fd[2], t_env *env)
{
	pid_t	pid;
	int		heredoc_fd;
	t_node	*tmp;

	tmp = setup_heredoc(node, &heredoc_fd, env);
	if (!tmp)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		if (heredoc_fd != -1)
			close(heredoc_fd);
		return (-1);
	}
	if (pid == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			exit(1);
		(close(fd[0]), close(fd[1]));
		if (heredoc_fd != -1)
		{
			if (dup2(heredoc_fd, STDIN_FILENO) < 0)
				exit(1);
			close(heredoc_fd);
		}
		executing(tmp, env);
		exit(1);
	}
	if (heredoc_fd != -1)
		close(heredoc_fd);
	return (pid);
}

static pid_t	right_pipe(t_node *node, int fd[2], t_env *env)
{
	pid_t	pid;
	int		heredoc_fd;
	t_node	*tmp;

	tmp = setup_heredoc(node, &heredoc_fd, env);
	pid = fork();
	if (pid < 0)
	{
		if (heredoc_fd != -1)
			close(heredoc_fd);
		return (-1);
	}
	if (pid == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) < 0)
			exit(1);
		(close(fd[0]), close(fd[1]));
		if (heredoc_fd != -1)
		{
			if (dup2(heredoc_fd, STDIN_FILENO) < 0)
				exit(1);
			close(heredoc_fd);
		}
		executing(tmp, env);
		exit(2);
	}
	if (heredoc_fd != -1)
		close(heredoc_fd);
	return (pid);
}

void	exec_pipe(t_node *node, t_env *env)
{
	pid_t	pid_read;
	pid_t	pid_write;
	int		status;
	int		fd[2];
	char		*exit_status;

	if (ft_pipe(fd) < 0)
		return ;
	pid_write = left_pipe(node->left, fd, env);
	if (pid_write < 0)
	{
		(close(fd[0]), close(fd[1]));
		return ;
	}
	pid_read = right_pipe(node->right, fd, env);
	if (pid_read < 0)
	{
		(close(fd[0]), close(fd[1]));
		return ;
	}
	(close(fd[0]), close(fd[1]));
	waitpid(pid_write, &status, 0);
	waitpid(pid_read, &status, 0);
	exit_status = ft_itoa(WEXITSTATUS(status));
	if (exit_status)
	{
		set_env_var(env, "?", exit_status);
		free(exit_status);
	}

}
