/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redire_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 05:26:24 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/02 18:22:59 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_open_input(char *file)
{
	int	fd;

	if (!file)
		return (print_error("minish", "ambiguous redirect", NULL, NULL), -1);
	fd = open(file, O_RDONLY, 00644);
	if (fd == -1)
		print_error("minish", (char *)file, strerror(errno), NULL);
	return (fd);
}

int	ft_open_output(char *file)
{
	int	fd;

	if (!file)
		return (print_error("minish", "ambiguous redirect", NULL, NULL), -1);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd == -1)
		print_error("minish", (char *)file, strerror(errno), NULL);
	return (fd);
}

int	ft_open_append(char *file)
{
	int	fd;

	if (!file)
		return (print_error("minish", "ambiguous redirect", NULL, NULL), -1);
	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 00644);
	if (fd == -1)
		print_error("minish", (char *)file, strerror(errno), NULL);
	return (fd);
}

int	preoredr_duplicat_file(t_node *node, t_env *env)
{
	if (!node)
		return (1);
	if (node->fd_in != 0)
		if (node->fd_in == -1 || ft_dup2(node->fd_in, STDIN_FILENO) < 0)
			return (exit_status(1, env), 0);
	if (node->fd_out != 1)
		if (node->fd_out == -1 || ft_dup2(node->fd_out, STDOUT_FILENO) < 0)
			return (exit_status(1, env), 0);
	if (!preoredr_duplicat_file(node->left, env))
		return (0);
	if (!preoredr_duplicat_file(node->right, env))
		return (0);
	return (1);
}
