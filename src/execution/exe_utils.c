/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:11:01 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/23 23:37:21 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pipe(int fd[2])
{
	int	ret;

	ret = pipe(fd);
	if (!ret)
		return (0);
	print_error("minish", "pipe", strerror(errno), NULL);
	exit_status(1);
	return (-1);
}

int	ft_dup2(int fd1, int fd2)
{
	int	ret;

	ret = dup2(fd1, fd2);
	if (ret != -1)
		return (ret);
	print_error("minish", "dup2", strerror(errno), NULL);
	exit_status(1);
	return (-1);
}

int	ft_close(int fd)
{
	int	ret;

	ret = close(fd);
	if (!ret)
		return (0);
	print_error("minish", "close", strerror(errno), NULL);
	exit_status(1);
	return (-1);
}

int	*setup_heredocs(t_node *node, int *heredoc_count)
{
	t_node *current;
	int *heredoc_fds;
	int count;
	int	i;
	int	j;

	count = 0;
	i  = -1;
	j  = 0;
	current = node;
	heredoc_fds = NULL;
	while (current && current->type == T_HERDOC)
	{
		count++;
		current = current->left;
	}

	*heredoc_count = count;
	if (count == 0)
		return NULL;
	heredoc_fds = malloc(sizeof(int) * count);
	if (!heredoc_fds)
		return NULL;
	current = node;
	while(++i < count)
	{
		heredoc_fds[i] = heredoc(current);
		if (heredoc_fds[i] < 0)
		{
			while (j < i)
				close(heredoc_fds[j++]);
			free(heredoc_fds);
			return NULL;
		}
		current = current->left;
	}
	return heredoc_fds;
}
