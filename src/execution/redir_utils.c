/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:42:51 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/30 14:30:30 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_open(const char *pathname, int flags, mode_t mode)
{
	int	fd;

	fd = open(pathname, flags, mode);
	if (fd == -1)
		print_error("minish", (char *)pathname, strerror(errno), NULL);
	return (fd);
}

int	setup_heredoc(t_node *node)
{
	int	heredoc_fd;

	heredoc_fd = -1;
	while (node && node->type == T_HERDOC)
	{
		if (heredoc_fd != -1)
			close(heredoc_fd);
		heredoc_fd = heredoc(node);
		if (heredoc_fd < 0)
			return (-1);
		node = node->left;
	}
	return (heredoc_fd);
}
