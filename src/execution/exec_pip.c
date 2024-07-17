/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:43:10 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/17 01:22:02 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <time.h>

static void	handle_left_child(t_node *node, t_env *env, int *fd, int *fdh)
{
	if (*fdh != 0)
	{
		while (node->left && node->left->type == T_HERDOC)
			node = node->left;
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	if (node->type == T_HERDOC)
		node = node->left;
	executing(node, env);
	exit(0);
}

static void	handle_right_child(t_node *node, t_env *env, int *fd, int *fdh)
{
	if (*fdh != 0)
	{
		while (node->left && node->left->type == T_HERDOC)
			node = node->left;
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (node->type == T_HERDOC)
		node = node->left;
	executing(node, env);
	exit(0);

}

static void	close_pipes_and_wait(int *fd, pid_t pid1, pid_t pid2, t_env *env)
{
	int		status;
	char	*exit_status;

	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	exit_status = ft_itoa(WEXITSTATUS(status));
	if (exit_status)
		(set_env_var(env, "?", exit_status), free(exit_status));
}

// void process_heredocs(t_node *node, t_env *env, int *fd)
// {
//     while (node || (node && node->left) || (node && node->right))
//     {
//         if (node && node->type == T_HERDOC)
//         {
//             if (redir_input(node, env, fd) < 0)
//                 return;
//         }
//
//         if (node && node->right && node->right->type == T_HERDOC)
//             node = node->right;
//         else if (node && node->left && node->left->type == T_HERDOC)
//             node = node->left;
//         else if (node)
//             node = node->right;
//         else
//             break;
//     }
// }
//

t_node	*process_heredocs(t_node *tmp, t_env *env, int *fdh)
{
	t_node *pipe;


	while (tmp && (tmp->right && tmp->left))
	{
		// if (tmp->right == T_CMD && tmp->left == T_CMD)
		// 	break ;
		if (tmp->type == T_PIPE)
			pipe = tmp;
		if (tmp->right && tmp->right->type == T_HERDOC)
		{
			redirections(tmp->right, env);
			*fdh = 1;
		}
		else if (tmp->left && tmp->left->type == T_HERDOC)
		{
			redirections(tmp->left, env);
			*fdh = 1;

		}
		tmp = tmp->right;
	}
	return (pipe);
}

void	exec_pipe(t_node *node, t_env *env)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int	fdh;

	fdh = 0;
	t_node	*tmp;
	t_node	*pip;

	tmp = node;
	pip = process_heredocs(tmp, env, &fdh);
	if (ft_pipe(fd) == -1)
		return ;
	pid1 = ft_fork();
	if (pid1 == -1)
		return ;
	if (pid1 == 0)
		handle_left_child(node->left, env, fd, &fdh);
	pid2 = ft_fork();
	if (pid2 == -1)
		return ;
	if (pid2 == 0)
		handle_right_child(node->right, env, fd, &fdh);
	close_pipes_and_wait(fd, pid1, pid2, env);
}

