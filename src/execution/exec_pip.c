/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:43:10 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/23 23:38:16 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static pid_t left_pipe(t_node *node, int fd[2])
{
	pid_t   pid;
	int     *heredoc_fds;
	int     heredoc_count;
	t_node  *tmp;
	int	i;

	tmp = node;
	i  = 0;
	heredoc_fds = setup_heredocs(node, &heredoc_count);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (ft_dup2(fd[1], STDOUT_FILENO) < 0)
			return (-1);
		if (ft_close(fd[1]) < 0)
			return (-1);
		if (ft_close(fd[0]) < 0)
			return (-1);

		if (heredoc_fds)
		{
			if (ft_dup2(heredoc_fds[heredoc_count - 1], STDIN_FILENO) < 0)
				return (-1);
			while (i < heredoc_count)
				close(heredoc_fds[i++]);
			free(heredoc_fds);
		}
		while (tmp && (tmp->type == T_HERDOC))
			tmp = tmp->left;
		executing(tmp);
		exit(minish.exit_status);
	}
	if (heredoc_fds)
	{
		i = 0;
		while (i < heredoc_count)
			close(heredoc_fds[i++]);
		free(heredoc_fds);
	}

	return (pid);
}
static	pid_t	right_pipe(t_node *node, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (ft_dup2(fd[0], STDIN_FILENO) < 0)
			return (-1);
		if (ft_close(fd[1]) < 0)
			return (-1);
		if (ft_close(fd[0]) < 0)
			return (-1);
		executing(node);
		exit(minish.exit_status);
	}
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
		return ;
	pid_read = right_pipe(node->right, fd);
	if (pid_read < 0)
		return ;
	if (ft_close(fd[1]) < 0)
		return ;
	if (ft_close(fd[0]) < 0)
		return ;
	waitpid(pid_read, &status, 0);
	waitpid(pid_write, &status, 0);
	exit_status(status);
}
