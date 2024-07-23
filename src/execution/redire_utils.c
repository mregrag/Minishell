/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redire_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 05:26:24 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/23 13:05:57 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_content(t_node *node, int fd, char *content, t_env *env)
{
	char	*new_content;

	if (node->flag == 1)
		ft_putendl_fd(content, fd);
	else
	{
		new_content = expansion_content(content, env);
		if (new_content)
			(ft_putendl_fd(new_content, fd), free(new_content));
	}
}

int	ft_open_input(char *file)
{
	int	fd;

	if (!file)
	{
		print_error("minish", "ambiguous redirect", NULL, NULL);
		return (-1);
	}
	fd = open(file, O_RDONLY, 00644);
	if (fd == -1)
		print_error("minish", (char *)file, strerror(errno), NULL);
	return (fd);
}

int	ft_open_output(char *file)
{
	int	fd;

	if (!file)
	{
		print_error("minish", "ambiguous redirect", NULL, NULL);
		return (-1);
	}
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd == -1)
		print_error("minish", (char *)file, strerror(errno), NULL);
	return (fd);
}

int	ft_open_append(char *file)
{
	int	fd;

	if (!file)
	{
		print_error("minish", "ambiguous redirect", NULL, NULL);
		return (-1);
	}
	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 00644);
	if (fd == -1)
		print_error("minish", (char *)file, strerror(errno), NULL);
	return (fd);
}

int	dfs_handle_redirections(t_node *node, t_env *env)
{
	if (!node)
		return (1);
	if (node->fd_in != 0)
		if (node->fd_in == -1 || ft_dup2(node->fd_in, STDIN_FILENO) < 0)
			return (exit_status(1, env), 0);
	if (node->fd_out != 1)
		if (node->fd_out == -1 || ft_dup2(node->fd_out, STDOUT_FILENO) < 0)
			return (exit_status(1, env), 0);
	if (!dfs_handle_redirections(node->left, env))
		return (0);
	if (!dfs_handle_redirections(node->right, env))
		return (0);
	return (1);
}
