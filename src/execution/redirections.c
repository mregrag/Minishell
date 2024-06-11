/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:05:58 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/11 15:56:47 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	fd_in(t_node *node)
{
	int		fd;
	t_node		*current;

	fd = 0;
	current = node;
	while (current->left)
	{
		if (current->type == T_IN)
		{
			if (fd)
				close(fd);
			fd = ft_open(current->right->cmd[0], O_RDONLY, 00644);
		}
		else if (current->type == T_HERDOC)
		{
			if (fd)
				close(fd);
			fd = current->fdh;
		}
		if (fd < 0)
			return (-1);
		current = current->left;
	}
	node->fd[0] = fd;
	return (0);
}

int	fd_out(t_node *node)
{
	int		fd;
	t_node *current;

	fd = 1;

	current = node;
	while (current->left)
	{
		if (current->type == T_OUT)
		{
			if (fd != 1)
				close(fd);
			fd = ft_open(current->right->cmd[0], (O_CREAT | O_WRONLY | O_TRUNC), 00644);
		}
		else if (current->type == T_APPEND)
		{
			if (fd != 1)
				close(fd);
			fd = ft_open(current->right->cmd[0], (O_CREAT | O_WRONLY | O_APPEND), 00644);
		}
		if (fd < 0)
			return (-1);
		current = current->left;
	}
	node->fd[1] = fd;
	return (0);
}

ssize_t	_write_(int fildes, const char *buf, size_t nbyte)
{
	if (write(fildes, buf, nbyte) < 0)
		return (print_error("minish", "write", strerror(errno), NULL),
			exit_status(1), -1);
	return (0);
}


int	handle_heredoc(char *delim)
{
	int		fd[2];
	char	*input;
	char	*save;

	pipe(fd);
	while (1)
	{
		input = readline("> ");
		if (!input || !ft_memcmp(input, delim, ft_strlen(input) + 1))
		{
			free(input);
			break ;
		}
		save = ft_strjoin(input, "\n");
		(free(input), input = save);
		_write_(fd[1], input, ft_strlen(input));
		(free(input), input = NULL);
	}
	return (close(fd[1]), fd[0]);
}

static	int	handle_in_out(t_node *root)
{
	if (fd_in(root) < 0 || fd_out(root) < 0)
		return (-1);
	return (0);
}

int	redirections(t_node *node)
{
	t_node	*current;

	current = node;
	while (current)
	{
		if (current->type == T_HERDOC)
		{
			current->fdh = handle_heredoc(current->right->cmd[0]);
			if (current->fdh < 0)
				return (-1);
		}
		if (!current->left)
			break;
		current = current->left;
	}
	if (handle_in_out(node) < 0)
		return (-1);
	return (0);
}

int	ft_redir(t_node *node)
{
	if (redirections(node) < 0)
		return (0);
	if (node->fd[0] != 0)
		if (dup2(node->fd[0], STDIN_FILENO) < 0)
			return (0);
	if (node->fd[1] != 1)
		if (dup2(node->fd[1], STDOUT_FILENO) < 0)
			return (0);
	if (node->fd[0] != 0)
		close(node->fd[0]);
	if (node->fd[1] != 1)
		close(node->fd[1]);
	return (1);
}
