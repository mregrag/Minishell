/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:58:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/10 22:34:23 by mkoualil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	update_status(int status)
{
	if (WIFSTOPPED(status))
		return (128 + WSTOPSIG(status));
	if (WIFSIGNALED(status))
	{
		if (128 + WTERMSIG(status) == 130)
			ft_putstr_fd("\n", 2);
		else if (128 + WTERMSIG(status) == 131)
			ft_putstr_fd("Quit: 3\n", 2);
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

char *get_path(char *command, t_env *env)
{
	char *path_var;
	char **paths;
	char *full_path;
	int i;

	i = 0;
	if (!command || !env)
		return (NULL);
	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	path_var = get_env_var(env, "PATH");
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	free(path_var);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full_path = ft_strjoin_three(paths[i], "/", command);
		if (!full_path)
			return (ft_free_array(paths), NULL);
		if (access(full_path, X_OK | F_OK) == 0)
			return (ft_free_array(paths), full_path);
		free(full_path);
		i++;
	}
	return (ft_free_array(paths), NULL);
}

static void setup_signal_handlers(struct sigaction *sa_ignore, struct sigaction *sa_default)
{
    sa_ignore->sa_handler = SIG_IGN;
    sigemptyset(&sa_ignore->sa_mask);
    sa_ignore->sa_flags = 0;

    sa_default->sa_handler = SIG_DFL;
    sigemptyset(&sa_default->sa_mask);
    sa_default->sa_flags = 0;
}

static void block_signals(struct sigaction *sa_ignore)
{
    sigaction(SIGINT, sa_ignore, NULL);
    sigaction(SIGQUIT, sa_ignore, NULL);
}

static void restore_signals(struct sigaction *sa_default)
{
    sigaction(SIGINT, sa_default, NULL);
    sigaction(SIGQUIT, sa_default, NULL);
}

static void	child_exec(t_node *node, t_env *env)
{
	char	**envp;
	char	*path;
	int	error;


	envp = ft_list_to_arr(env->env);
	if (!envp)
		exit(1);

	path = get_path(node->cmd[0], env);
	if (path)
		execve(path, node->cmd, envp);
	error = exec_err(path, node->cmd[0]);
	free(path);
	ft_free_array(envp);
	exit(error);
}

void	exec_cmd(t_node *node, t_env *env)
{
	pid_t	pid;
	int	status;
	char	*exit_status;
	struct sigaction sa_ignore;
    struct sigaction  sa_default;
	if (!node->cmd || !node->cmd[0])
		return ;
	setup_signal_handlers(&sa_ignore, &sa_default);
    block_signals(&sa_ignore);
	pid = ft_fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		restore_signals(&sa_default);
		child_exec(node, env);
	}
	else
	{
		waitpid(pid, &status, 0);
		exit_status = ft_itoa(update_status(status));
		set_env_var(env, "?", exit_status);
		free(exit_status);
	}
	set_env_var(env, "_", node->cmd[ft_strlen_arg(node->cmd) - 1]);
}
