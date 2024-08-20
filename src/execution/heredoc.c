/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 04:11:35 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/20 06:04:50 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	write_content(t_node *node, int fd, char *content, t_env *env)
{
	char	*new_content;

	if (node->flag == 1)
		ft_putendl_fd(content, fd);
	else
	{
		new_content = expand_heredoc(content, env);
		(ft_putendl_fd(new_content, fd), free(new_content));
	}
}

static int	heredoc(t_node *node, t_env *env)
{
	int		fd[2];
	char	*content;
	char	*dilim;

	if (ft_pipe(fd) < 0)
		return (-1);
	set_signal_heredoc();
	node->flag = ft_strchr(node->cmd[0], '\'') || ft_strchr(node->cmd[0], '"');
	dilim = remove_quotes(node->cmd[0]);
	while (1)
	{
		content = readline("> ");
		if (!ttyname(0))
			return (free(content), free(dilim), close(fd[0]), close(fd[1]), -1);
		if (!content)
			break ;
		if (!node->cmd[0] || !ft_strcmp(content, dilim))
		{
			free(content);
			break ;
		}
		write_content(node, fd[1], content, env);
		free(content);
	}
	return (free(dilim), close(fd[1]), exit_status(0, env), fd[0]);
}

static int	open_heredocs(t_node *node, t_env *env)
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
	if (!open_heredocs(node, env))
		return ;
	preorder_hearedoc(node->left, env);
	preorder_hearedoc(node->right, env);
}
