/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 04:11:35 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/07 00:43:12 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	heredoc_content(t_node *node, int fd, char *content, t_env *env)
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

static int	process_heredoc_content(t_node *node, int *fd_heredoc, t_env *env)
{
	char	*content;
	char	*dilim;

	dilim = expansion_dilim(node->cmd[0]);
	while (1)
	{
		content = readline("> ");
		if (!ttyname(0))
			return (free(content), free(dilim), -1);
		if (!content)
			return (free(dilim), 0);
		if (!dilim || !ft_strcmp(content, dilim))
		{
			(free(content));
			break ;
		}
		heredoc_content(node, fd_heredoc[1], content, env);
		free(content);
	}
	return (free(dilim), 0);
}

static int	heredoc(t_node *node, t_env *env)
{
	int	fd_heredoc[2];

	if (ft_pipe(fd_heredoc) < 0)
		return (-1);
	set_signal_heredoc();
	node->flag = ft_strchr(node->cmd[0], '\'') || ft_strchr(node->cmd[0], '"');
	if (process_heredoc_content(node, fd_heredoc, env) < 0)
		return (close(fd_heredoc[0]), close(fd_heredoc[1]), -1);
	close(fd_heredoc[1]);
	return (fd_heredoc[0]);
}

static int	heredoc_redirection(t_node *node, t_env *env)
{
	if (node->right && node->right->cmd)
	{
		if (node->type == T_HERDOC)
			node->fd_in = heredoc(node->right, env);
		if (node->fd_in == -1)
			return (exit_status(1, env), 0);
	}
	return (1);
}

void	preorder_hearedoc(t_node *node, t_env *env)
{
	if (!node || g_sig == -1)
		return ;
	if (!heredoc_redirection(node, env))
		return ;
	preorder_hearedoc(node->left, env);
	preorder_hearedoc(node->right, env);
}
