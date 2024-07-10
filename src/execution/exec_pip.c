/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:43:10 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/10 19:03:52 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

static void	child_process(t_node *node, int fd[2], int is_left, t_env *env)
{
	if (is_left)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	executing(node, env);
	exit(ft_atoi(get_env_var(env, "?")));
}

void	exec_pipe(t_node *node, t_env *env)
{
	char	*exit_status;
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;
	int		fd[2];

	if (ft_pipe(fd) < 0)
		return ;
	pid_left = ft_fork();
	if (pid_left == 0)
		child_process(node->left, fd, 1, env);
	else if (pid_left < 0)
		return (close_pipe(fd));
	pid_right = ft_fork();
	if (pid_right == 0)
		child_process(node->right, fd, 0, env);
	else if (pid_right < 0)
		return (close_pipe(fd));
	close_pipe(fd);
	(waitpid(pid_left, &status, 0), waitpid(pid_right, &status, 0));
	exit_status = ft_itoa(WEXITSTATUS(status));
	if (exit_status)
		(set_env_var(env, "?", exit_status), free(exit_status));
}
