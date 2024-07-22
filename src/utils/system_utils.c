/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 04:37:41 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/21 20:43:48 by mregrag          ###   ########.fr       */
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

void	cleanup_fds(t_node *node)
{
	if (!node)
		return ;
	if (node->fd_in > 2)
		close(node->fd_in);
	if (node->fd_out > 2)
		close(node->fd_out);
	cleanup_fds(node->left);
	cleanup_fds(node->right);
}
