/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:58:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/03 23:46:15 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/wait.h>

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

static void	child_exec(t_node *node, t_env *env)
{
	char	**envp;
	pid_t	pid;
	int		status;
	char	*path;

	envp = ft_list_to_arr(env->env);
	if (!env)
		return ;
	pid = ft_fork();
	if (pid < 0)
	{
		ft_free_array(envp);
		return ;
	}
	if (pid == 0)
	{
		path = get_path(node->cmd[0], env);
		if (!path)
		{
			ft_free_array(envp);
			exit(exec_err(errno, NULL, node->cmd[0]));
		}
		execve(path, node->cmd, envp);
		free(path);
		//ft_free_array(env);
		exit(exec_err(errno, path, node->cmd[0]));
	}
	else
	{
		//ft_free_array(env);
		waitpid(pid, &status, 0);
		set_env_var(env, "?", ft_itoa(WEXITSTATUS(status)));
	}
}

void	exec_cmd(t_node *node, t_env *env)
{
	if (redirections(node, env))
	{
		while (node->left)
			node = node->left;
	}
	if (node->cmd && node->cmd[0] && !is_builtin(node, env))
		child_exec(node, env);
}

