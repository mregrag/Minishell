/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:05:58 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/23 18:05:46 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	heredoc(t_node *node)
{
	int		fd[2];
	char	*str;

	if (ft_pipe(fd) < 0)
		return (-1);
	while (1)
	{
		str = readline("> ");
		if (!str || ft_strcmp(str, node->right->cmd[0]) == 0)
		{
			free(str);
			break ;
		}
		write(fd[1], str, ft_strlen(str));
		write(fd[1], "\n", 1);
		free(str);
		str = NULL;
	}
	close(fd[1]);
	return (fd[0]);
}

static int	redir_input(t_node *node)
{
	int		fd;
	t_node	*tmp;

	fd = 0;
	tmp = node;
	while (tmp)
	{
		if (tmp->type == T_IN)
			fd = ft_open(tmp->right->cmd[0], O_RDONLY, 00644);
		else if (tmp->type == T_HERDOC)
			fd = heredoc(tmp);
		if (fd < 0)
			return (-1);
		tmp = tmp->left;
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
	t_node	*tmp;

	fd = 1;
	tmp = node;
	while (tmp)
	{
		if (tmp->type == T_OUT)
			fd = ft_open(tmp->right->cmd[0], (O_CREAT | O_WRONLY | O_TRUNC), 00644);
		else if (tmp->type == T_APPEND)
			fd = ft_open(tmp->right->cmd[0], (O_CREAT | O_WRONLY | O_APPEND), 00644);
		if (fd < 0)
			return (-1);
		tmp = tmp->left;
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
