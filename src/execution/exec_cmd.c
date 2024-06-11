/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:58:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/11 01:09:29 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_path_command(char *cmd)
{
	char	**paths;
	char	*cmd_path;
	char	*path;

	if (!ft_getenv("PATH"))
		return (print_error("minish", cmd, "No sush file or directory", NULL), NULL);
	paths = ft_split(ft_getenv("PATH"), ':');
	while (*paths)
	{
		path = ft_strjoin(*paths, "/");
		cmd_path = ft_strjoin(path, cmd);
		free (path);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
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
		if (execve(path, node->cmd, ft_list_to_arr(minish.env)) == -1)
		{
			print_error("minish", node->cmd[0], "command not found", NULL);
			exit(127);
		}
	waitpid(pid, status, 0);
}

void	exec_cmd(t_node *node)
{
	int		status;
	char	*path;

	if (node->type >= T_IN && node->type <= T_HERDOC)
	{
		if (!ft_redir(node))
			return ;
		while (node->left)
			node = node->left;
		executing(node->left);
	}
	if (node->cmd && node->cmd[0] && !is_builtin(node->cmd))
	{
		path = get_path_command(node->cmd[0]);
		if (!path)
			return ;
		child_exec(node, path, &status);
		free(path);
		exit_status(WEXITSTATUS(status));
	}
}
