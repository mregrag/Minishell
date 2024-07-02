/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:58:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/02 20:37:55 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*cmd_path;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	if (get_env_var(env, "PATH"))
		paths = ft_split(get_env_var(env, "PATH"), ':');
	else
		return (NULL);
	while (*paths)
	{
		cmd_path = ft_strjoin(ft_strjoin(*paths, "/"), cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		paths++;
	}
	return (ft_strdup(cmd));
}

static	void	child_exec(t_node *node)
{
	char	**env;
	pid_t	pid;
	int		status;

	env = ft_list_to_arr(node->env->env);
	if (!env)
		return ;
	pid = ft_fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		execve(get_path(node->cmd[0], node->env), node->cmd, env);
		exit(exec_err(errno, get_path(node->cmd[0], node->env), node->cmd[0]));
	}
	waitpid(pid, &status, 0);
	exit_status(WEXITSTATUS(status), node);
}

void	exec_cmd(t_node *node)
{
	if (redirections(node))
		while (node->left)
			node = node->left;
	if (node->cmd && node->cmd[0] && !is_builtin(node))
		child_exec(node);
}
