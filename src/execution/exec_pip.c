/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:43:10 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/02 00:13:25 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static pid_t	left_pipe(t_node *node, int fd[2])
{
	pid_t	pid;
	int		heredoc_fd;
	t_node	*tmp;

	tmp = setup_heredoc(node, &heredoc_fd);
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
		executing(tmp);
		exit(ft_atoi(get_env_var(node->env, "?")));
	}
	if (heredoc_fd != -1)
		close(heredoc_fd);
	return (pid);
}

static pid_t	right_pipe(t_node *node, int fd[2])
{
	pid_t	pid;
	int		heredoc_fd;
	t_node	*tmp;

	tmp = setup_heredoc(node, &heredoc_fd);
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
		executing(tmp);
		exit(ft_atoi(get_env_var(node->env, "?")));
	}
	if (heredoc_fd != -1)
		close(heredoc_fd);
	return (pid);
}

void	exec_pipe(t_node *node)
{
	pid_t	pid_read;
	pid_t	pid_write;
	int		status;
	int		fd[2];

	if (ft_pipe(fd) < 0)
		return ;
	pid_write = left_pipe(node->left, fd);
	if (pid_write < 0)
	{
		(close(fd[0]), close(fd[1]));
		return ;
	}
	pid_read = right_pipe(node->right, fd);
	if (pid_read < 0)
	{
		(close(fd[0]), close(fd[1]));
		return ;
	}
	(close(fd[0]), close(fd[1]));
	waitpid(pid_write, &status, 0);
	waitpid(pid_read, &status, 0);
	update_env_var("?", ft_itoa(WEXITSTATUS(status)), node);
}
