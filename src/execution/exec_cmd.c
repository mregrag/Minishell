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
	char	*path;
	char	*result;
	char	*temp;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = get_env_var(env, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	result = NULL;
	while (*paths)
	{
		temp = ft_strjoin(*paths, "/");
		if (!temp)
		{
			ft_free_array(paths);
			return (NULL);
		}
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!cmd_path)
		{
			ft_free_array(paths);
			return (NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			result = cmd_path;
			break;
		}
		free(cmd_path);
		paths++;
	}
	//ft_free_array(paths);
	if (result)
		return (result);
	return (ft_strdup(cmd));
}
static void	child_exec(t_node *node)
{
	char	**env;
	pid_t	pid;
	int		status;
	char	*path;

	env = ft_list_to_arr(node->env->env);
	if (!env)
		return ;
	pid = ft_fork();
	if (pid < 0)
	{
		ft_free_array(env);
		return ;
	}
	if (pid == 0)
	{
		path = get_path(node->cmd[0], node->env);
		if (!path)
		{
			ft_free_array(env);
			exit(exec_err(errno, NULL, node->cmd[0]));
		}
		execve(path, node->cmd, env);
		free(path);
		//ft_free_array(env);
		exit(exec_err(errno, path, node->cmd[0]));
	}
	else 
	{
		//ft_free_array(env);
		waitpid(pid, &status, 0);
		// You might want to handle the exit status here
		// For example: g_exit_status = WEXITSTATUS(status);
	}
}

void	exec_cmd(t_node *node)
{
	if (redirections(node))
	{
		while (node->left)
			node = node->left;
	}
	if (node->cmd && node->cmd[0] && !is_builtin(node))
		child_exec(node);
}

