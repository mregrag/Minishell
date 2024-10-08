/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:58:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/20 04:00:54 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	update_status(int status)
{
	if (WIFSTOPPED(status))
		return (128 + WSTOPSIG(status));
	if (WIFSIGNALED(status))
	{
		if (128 + WTERMSIG(status) == 130)
			ft_putstr_fd("\n", 1);
		else if (128 + WTERMSIG(status) == 131)
			ft_putstr_fd("Quit: 3\n", 1);
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

char	*get_path(char *command, t_env *env)
{
	char	**paths;
	char	*full_path;
	char	*value;
	int		i;

	i = 0;
	if (!command || !env || ft_strchr(command, '/'))
		return (command);
	value = get_env_var(env, "PATH");
	paths = ft_split(value, ':');
	free(value);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full_path = ft_strjoin_three(paths[i], "/", command);
		if (access(full_path, X_OK | F_OK) == 0)
			return (ft_free_array(paths), full_path);
		free(full_path);
		i++;
	}
	return (ft_free_array(paths), NULL);
}

static void	child_execute(t_node *node, t_env *env)
{
	char	**envp;
	char	*path;
	int		error;

	error = 0;
	envp = ft_list_to_arr(env->env);
	if (!envp)
		exit(1);
	path = get_path(node->cmd[0], env);
	if (execve(path, node->cmd, envp) == -1)
		error = exec_err(path, node->cmd[0], env);
	free(path);
	ft_free_array(envp);
	exit(error);
}

void	execute_command(t_node *node, t_env *env)
{
	struct sigaction	sa_ignore;
	struct sigaction	sa_default;
	pid_t				pid;
	char				*exit_status;
	int					status;

	if (!node || !node->cmd || !node->cmd[0])
		return ;
	signal_handlers(&sa_ignore, &sa_default);
	block_signals(&sa_ignore);
	pid = ft_fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		restore_signals(&sa_default);
		child_execute(node, env);
	}
	else
	{
		waitpid(pid, &status, 0);
		exit_status = ft_itoa(update_status(status));
		(set_env_var(env, "?", exit_status), free(exit_status));
		set_env_var(env, "_", node->cmd[ft_strlen_arg(node->cmd) - 1]);
	}
}
