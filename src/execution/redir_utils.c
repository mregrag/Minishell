/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:42:51 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/24 14:20:15 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_open(const char *path, int oflag, mode_t mode)
{
	int	fd;

	fd = open(path, oflag, mode);
	if (fd != -1)
		return (fd);
	print_error("minish", (char *)path, strerror(errno), NULL);
	exit_status(1);
	return (-1);
}

int	*setup_heredocs(t_node *node, int *heredoc_count)
{
	t_node	*current = node;
	int		count = 0, i = 0;
	int		*heredoc_fds = NULL;

	while (current && current->type == T_HERDOC)
	{
		count++;
		current = current->left;
	}
	*heredoc_count = count;
	if (count == 0)
		return NULL;
	if (!(heredoc_fds = malloc(sizeof(int) * count)))
		return NULL;
	current = node;
	while (i < count)
	{
		if ((heredoc_fds[i] = heredoc(current)) < 0)
		{
			while (--i >= 0)
				close(heredoc_fds[i]);
			free(heredoc_fds);
			return NULL;
		}
		current = current->left;
		i++;
	}
	return heredoc_fds;
}
