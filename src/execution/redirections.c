/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:05:58 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/11 18:46:24 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_sig;

int	heredoc(t_node *node, t_env *env)
{
	char	*content;
	char	*dilim;
	int		fd[2];

	if (ft_pipe(fd) < 0)
		return (-1);
	set_signal_heredoc();
	node->flag = ft_strchr(node->cmd[0], '\'') || ft_strchr(node->cmd[0], '"');
	while (1)
	{
		content = readline("> ");
		if (!ttyname(0))
			return (free(content), close(fd[1]), close(fd[0]), -1);
		dilim = expansion_dilim(node->cmd[0]);
		if (!dilim || !ft_strcmp(content, dilim))
			break ;
		heredoc_content(node, fd[1], content, env);
		free(content);
		free(dilim);
	}
	return (free(content), free(dilim), close(fd[1]), fd[0]);
}

static int	redir_input(t_node *node, t_env *env, int *fd)
{
	t_node	*current;

	*fd = 0;
	current = node;
	if (!check_file(current))
		return (-1);
	while (current)
	{
		if (current->type == T_IN)
		{
			if (*fd != 0)
				close(*fd);
			*fd = ft_open(current->right->cmd[0], O_RDONLY, 00644);
		}
		else if (current->type == T_HERDOC)
		{
			if (*fd != 0)
				close(*fd);
			*fd = heredoc(current->right, env);
		}
		if (*fd < 0)
			return (-1);
		current = current->left;
	}
	return (0);
}

static int	redire_output(t_node *node, int *fd)
{
	t_node	*current;

	*fd = 1;
	current = node;
	if (!check_file(current))
		return (-1);
	while (current)
	{
		if (current->type == T_OUT)
		{
			if (*fd != 1)
				close(*fd);
			*fd = ft_open(current->right->cmd[0], OUT_FLAG, 00644);
		}
		else if (current->type == T_APPEND)
		{
			if (*fd != 1)
				close(*fd);
			*fd = ft_open(current->right->cmd[0], APP_FLAG, 00644);
		}
		if (*fd < 0)
			return (-1);
		current = current->left;
	}
	return (0);
}

int	redirections(t_node *node, t_env *env)
{
	int	fd_in;
	int	fd_out;

	fd_in = 0;
	fd_out = 1;
	if (redir_input(node, env, &fd_in) < 0 || redire_output(node, &fd_out) < 0)
		return (0);
	if (fd_in != 0)
	{
		if (ft_dup2(fd_in, 0) < 0)
			return (0);
		close(fd_in);
	}
	if (fd_out != 1)
	{
		if (ft_dup2(fd_out, STDOUT_FILENO) < 0)
			return (0);
		close(fd_out);
	}
	return (1);
}
