/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:42:51 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/03 19:45:15 by mregrag          ###   ########.fr       */
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

t_node	*setup_heredoc(t_node *node, int *heredoc_fd, t_env *env)
{
	*heredoc_fd = -1;
	while (node && node->type == T_HERDOC)
	{
		if (*heredoc_fd != -1)
			close(*heredoc_fd);
		*heredoc_fd = heredoc(node, env);
		if (*heredoc_fd < 0)
			return (NULL);
		node = node->left;
	}
	return (node);
}
