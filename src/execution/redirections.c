/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:05:58 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/10 23:55:42 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int g_sig;

int	heredoc(t_node *node, t_env *env)
{
	char	*str;
	char	*exp_str;
	char	*dilim;
	int		fd[2];

	if (ft_pipe(fd) < 0)
		return (-1);
	set_signal_heredoc();
	while (1)
	{
		if (ft_strchr(node->right->cmd[0], '\'') || ft_strchr(node->right->cmd[0], '"'))
			node->flag = 1;
		str = readline("> ");
		if(!ttyname(0))
		{	g_sig = -1;
			return (free(str), -1);
		}
		if (!str)
			break ;
		dilim = expansion_dilim(node->right->cmd[0]);
		if (!dilim || !ft_strcmp(str, dilim))
		{
			(free(str), free(dilim));
			break ;
		}
		free(dilim);
		if (node->flag == 1)
			ft_putendl_fd(str, fd[1]);
		else
		{
			exp_str = expansion_content(str, env);
			if (exp_str)
				(ft_putendl_fd(exp_str, fd[1]), free(exp_str));
		}
		free(str);
	}
	return (ft_close(fd[1]), fd[0]);
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
			*fd = heredoc(current, env);
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
		if (dup2(fd_in, STDIN_FILENO) < 0)
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
