/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:58:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/29 21:13:26 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

char	*get_path(char *cmd, t_list *env)
{
	char	**paths;
	char	*cmd_path;

	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	if (!ft_getenv("PATH", env))
		return (print_error("minish1", cmd, strerror(errno), NULL), NULL);
	paths = ft_split(ft_getenv("PATH", env), ':');
	while (*paths)
	{
		cmd_path = ft_strjoin(ft_strjoin(*paths, "/"), cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		ft_free(&cmd_path);
		paths++;
	}
	return (ft_strdup(cmd));
}

static	void	executing_cmd(t_node *node, char **env)
{
	if (execve(get_path(node->cmd[0], node->env), node->cmd, env) == -1)
	{
		if (errno == ENOENT)
		{
			print_error("minish2", node->cmd[0], "command not found", NULL);
			exit(127);
		}
		else if (opendir(node->cmd[0]))
		{
			print_error("minish2", node->cmd[0], "is a directory", NULL);
			exit (126);
		}
		print_error("minish2", node->cmd[0], "command not found", NULL);
		exit(127);
	}
}

static	void	child_exec(t_node *node, int *status)
{
	char	**env;
	pid_t	pid;

	env = ft_list_to_arr(node->env);
	if (!env)
		return ;
	pid = ft_fork();
	if (pid < 0)
		return ;
	if (pid == 0)
		executing_cmd(node, env);
	waitpid(pid, status, 0);
}

void	exec_cmd(t_node *node)
{
	int		status;

	if (redirections(node))
		while (node->left)
			node = node->left;
	if (node->cmd && node->cmd[0] && !is_builtin(node))
		child_exec(node, &status);
	update_env_var("?", ft_itoa(WEXITSTATUS(status)), node);
}
