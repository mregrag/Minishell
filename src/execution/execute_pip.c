/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:43:10 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/22 06:12:45 by mkoualil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	execute_left_command(t_node *node, t_env *env, int *pipfd)
{
	close(pipfd[0]);
	dup2(pipfd[1], STDOUT_FILENO);
	close(pipfd[1]);
	executing(node, env);
	exit(ft_atoi(get_env_var(env, "?")));
}

static void	execute_right_command(t_node *node, t_env *env, int *pipfd)
{
	close(pipfd[1]);
	dup2(pipfd[0], STDIN_FILENO);
	close(pipfd[0]);
	executing(node, env);
	exit(ft_atoi(get_env_var(env, "?")));
}

static void	wait_for_children(pid_t pid1, pid_t pid2, t_env *env, int *pipfd)
{
	int		status;
	char	*exit_status;

	close(pipfd[0]);
	close(pipfd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	exit_status = ft_itoa(WEXITSTATUS(status));
	if (exit_status)
	{
		set_env_var(env, "?", exit_status);
		free(exit_status);
	}
	(void) env;
}



void	execute_pipe(t_node *node, t_env *env)
{
	pid_t					pid1;
	pid_t					pid2;
	struct sigaction	sa_ignore;
	struct sigaction	sa_default;
	int	pipfd[2];

	signal_handlers(&sa_ignore, &sa_default);
	block_signals(&sa_ignore);
	if (ft_pipe(pipfd) == -1)
		return ;
	pid1 = ft_fork();
	if (pid1 == -1)
	{
		(close(pipfd[0]), close(pipfd[1]));
		return ;
	}
	if (pid1 == 0){
		execute_left_command(node->left, env, pipfd);

	}
	pid2 = ft_fork();
	if (pid2 == -1)
	{
		(close(pipfd[0]), close(pipfd[1]));
		return ;
	}
	if (pid2 == 0){
		execute_right_command(node->right, env, pipfd);
	}
	wait_for_children(pid1, pid2, env, pipfd);
}
