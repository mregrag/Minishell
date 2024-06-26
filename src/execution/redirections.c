/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:05:58 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/30 19:08:51 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc(t_node *node)
{
	int		fd[2];
	char	*str;

	if (ft_pipe(fd) < 0)
		return (-1);
	while (1)
	{
		str = readline("> ");
		if (!str || ft_strcmp(str, expansion_dilim(node->right->cmd[0], node)) == 0)
		{
			ft_free(&str);
			break;
		}
		if (node->flag == 1)
			ft_putendl_fd(str, fd[1]);
		else
			ft_putendl_fd(expansion_content(str, node), fd[1]);
		ft_free(&str);
	}
	ft_close(fd[1]);
	return (fd[0]);
}

static int	check_file(t_node *node)
{
	t_node	*current;
	char	*str;

	current = node;
	while (current)
	{
		if (current->right && !current->right->cmd[0])
		{
			str = current->right->cmd[0];
			print_error("minish", str, "ambiguous redirect", NULL);
			return (0);
		}
		current = current->left;
	}
	return (1);
}

static int	redir_input(t_node *node)
{
	int		fd;
	t_node	*current;

	fd = 0;
	current = node;
	if (!check_file(current))
		return (-1);
	while (current)
	{
		if (current->type == T_IN)
		{
			if (fd != 0)
				close(fd);
			fd = ft_open(current->right->cmd[0], O_RDONLY, 00644);
		}
		else if (current->type == T_HERDOC)
		{
			if (fd != 0)
				close(fd);
			fd = heredoc(current);
		}
		if (fd < 0)
			return (-1);
		current = current->left;
	}
	if (fd != 0)
		if (dup2(fd, STDIN_FILENO) < 0)
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
	if (!check_file(current))
		return (-1);
	while (current)
	{
		if (current->type == T_OUT)
		{
			if (fd != 1)
				close(fd);
			fd = ft_open(current->right->cmd[0], O_CREAT | O_WRONLY | O_TRUNC, 00644);
		}
		else if (current->type == T_APPEND)
		{
			if (fd != 1)
				close(fd);
			fd = ft_open(current->right->cmd[0], O_CREAT | O_WRONLY | O_APPEND, 00644);
		}
		current = current->left;
	}
	if (fd < 0)
		return (-1);
	if (fd != 1)
		if (ft_dup2(fd, STDOUT_FILENO) < 0)
			return (0);
	if (fd != 1)
		close(fd);
	return (0);
}

int	redirections(t_node *node)
{
	if (is_redirection(node->type))
	{
		if (redir_input(node) < 0 || redire_output(node) < 0)
			return (0);
	}
	return (1);
}

