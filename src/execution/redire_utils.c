/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redire_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 05:26:24 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/12 23:06:25 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_open_input(char *file)
{
	int	fd;

	if (ft_is_empty_string(file))
		return (print_error("minish", "ambiguous redirect", NULL, NULL), -1);
	fd = open(file, O_RDONLY, 00644);
	if (fd == -1)
		print_error("minish", (char *)file, strerror(errno), NULL);
	return (fd);
}

int	ft_open_output(char *file)
{
	int	fd;

	if (ft_is_empty_string(file))
		return (print_error("minish", "ambiguous redirect", NULL, NULL), -1);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd == -1)
		print_error("minish", (char *)file, strerror(errno), NULL);
	return (fd);
}

int	ft_open_append(char *file)
{
	int	fd;

	if (ft_is_empty_string(file))
		return (print_error("minish", "ambiguous redirect", NULL, NULL), -1);
	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 00644);
	if (fd == -1)
		print_error("minish", (char *)file, strerror(errno), NULL);
	return (fd);
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

int	duplicat_file(t_node *node)
{
	while (node)
	{
		if (node->fd_in != 0)
			if (node->fd_in == -1 || ft_dup2(node->fd_in, STDIN_FILENO) < 0)
				return (0);
		if (node->fd_out != 1)
			if (node->fd_out == -1 || ft_dup2(node->fd_out, STDOUT_FILENO) < 0)
				return (0);
		// if (node->fd_in != 0)
		// 	close (node->fd_in);
		// if (node->fd_out != 1)
		// 	close (node->fd_out);
		node = node->left;
	}
	return (1);
}
