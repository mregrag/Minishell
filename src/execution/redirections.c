/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:05:58 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/24 17:47:53 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc(t_node *node)
{
	int		fd[2];
	char	*str;
	pid_t	pid;

	if (ft_pipe(fd) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		(close(fd[0]), close(fd[1]));
		return (-1);
	}
	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			str = readline("> ");
			if (!str || ft_strcmp(str, node->right->cmd[0]) == 0)
				(free(str), close(fd[1]), exit(0));
			ft_putendl_fd(str, fd[1]);
			(free(str), str = NULL);
		}
	}
	else
		(close(fd[1]), waitpid(pid, NULL, 0));
	return (fd[0]);
}

static int	redir_input(t_node *node)
{
	int		fd;
	t_node	*current;

	fd = 0;
	current = node;
	while (current)
	{
		if (current->type == T_IN)
			fd = ft_open(current->right->cmd[0], O_RDONLY, 00644);
		if (current->type == T_HERDOC)
			fd = heredoc(current);
		if (fd < 0)
			return (-1);
		current = current->left;
	}
	if (fd != 0 && ft_dup2(fd, STDIN_FILENO) < 0)
		return (0);
	if (fd != 0)
		close(fd);
	return (0);
}

static int	redire_output(t_node *node)
{
	int		fd;
	t_node	*current;

	fd = 1;
	current = node;
	while (current)
	{
		if (current->type == T_OUT)
			fd = ft_open(current->right->cmd[0], (O_CREAT | O_WRONLY | O_TRUNC), 00644);
		else if (current->type == T_APPEND)
			fd = ft_open(current->right->cmd[0], (O_CREAT | O_WRONLY | O_APPEND), 00644);
		if (fd < 0)
			return (-1);
		current = current->left;
	}
	if (fd != 1 && ft_dup2(fd, STDOUT_FILENO) < 0)
		return (0);
	if (fd != 1)
		close(fd);
	return (0);
}

int	redirections(t_node *node)
{
	if (redir_input(node) < 0 || redire_output(node) < 0)
		return (-1);
	return (1);
}
