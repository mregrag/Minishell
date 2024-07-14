/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:43:10 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/14 21:18:23 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

void	close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

static void	child_process(t_node *node, t_fd *data, int is_left, t_env *env)
{
	int	std_fd;

	if (is_left)
		std_fd = STDOUT_FILENO;
	else
		std_fd = STDIN_FILENO;
	if (ft_dup2(data->fd[is_left], std_fd) < 0)
		exit(1);
	close_pipe(data->fd);
	// printf("d = %d\n", data->fdh);
	if (data->fdh != 0)
	{
		if (ft_dup2(data->fdh, STDIN_FILENO) < 0)
			exit(1);
		close(data->fdh);
	}
	executing(node, env);
	exit(ft_atoi(get_env_var(env, "?")));
}

static void	parent_process(t_fd *data, pid_t left, pid_t right, t_env *env)
{
	int		status;
	char	*exit_status;

	close_pipe(data->fd);
	waitpid(left, &status, 0);
	waitpid(right, &status, 0);
	exit_status = ft_itoa(WEXITSTATUS(status));
	if (exit_status)
	{
		set_env_var(env, "?", exit_status);
		free(exit_status);
	}
}

static int	setup_and_fork(t_node *left, t_node *right, t_fd *data, t_env *env)
{
	pid_t	pid_left;
	pid_t	pid_right;

	if (ft_pipe(data->fd) < 0)
		return (-1);
	pid_left = ft_fork();
	if (pid_left == 0)
		child_process(left, data, 1, env);
	else if (pid_left < 0)
		return (close_pipe(data->fd), -1);
	pid_right = ft_fork();
	if (pid_right == 0)
		child_process(right, data, 0, env);
	else if (pid_right < 0)
		return (close_pipe(data->fd), -1);
	parent_process(data, pid_left, pid_right, env);
	return (0);
}

void	exec_pipe(t_node *node, t_env *env)
{
	t_node		*tmp;
	t_fd		data;
	int			result;

	data.fdh = 0;
	tmp = find_heredoc(node);
	if (tmp)
	{
		if (redir_input(tmp, env, &data.fdh) < 0)
			return ;
		result = setup_and_fork(tmp->left, tmp->right, &data, env);
	}
	else
		result = setup_and_fork(node->left, node->right, &data, env);
	if (result < 0)
	{
		if (data.fdh != 0)
			close(data.fdh);
		return ;
	}
	if (data.fdh != 0)
		close(data.fdh);
}
