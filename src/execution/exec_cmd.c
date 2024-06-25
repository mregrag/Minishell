/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:58:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/25 20:08:04 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_path(char *cmd)
{
	char	**paths;
	char	*cmd_path;

	if (!ft_getenv("PATH") && !g_minish.dpath)
		return (print_error("minish", cmd, strerror(errno), NULL), NULL);
	paths = ft_split(ft_getenv("PATH"), ':');
	while (*paths)
	{
		cmd_path = ft_strjoin(ft_strjoin(*paths, "/"), cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		cmd_path = NULL;
		paths++;
	}
	return (cmd);
}

static	void	child_exec(t_node *node, char *path, int *status)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (execve(path, node->cmd, ft_list_to_arr(g_minish.env)) == -1)
		{
			print_error("minish", node->cmd[0], strerror(errno), NULL);
			exit(127);
		}
	}
	waitpid(pid, status, 0);
}

void	exec_cmd(t_node *node)
{
	int		status;
	char	*path;

	if (is_redirection(node->type))
	{
		if (!redirections(node))
			return ;
		while (node->left)
			node = node->left;
	}
	if (node->cmd && node->cmd[0] && !is_builtin(node->cmd))
	{
		path = get_path(node->cmd[0]);
		if (!path)
			return ;
		child_exec(node, path, &status);
		free(path);
		path = NULL;
		exit_status(WEXITSTATUS(status));
	}
}
