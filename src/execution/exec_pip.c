/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:43:10 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/16 12:09:13 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

static void	handle_left_child(t_node *node, t_env *env, int *fd, int *fdh)
{
	// if (fdh != 0)
	// {
	// 	dup2(*fdh, STDOUT_FILENO);
	// 	close(fd[1]);
	// 	close(fd[0]);
	// 	executing(node->left, env);
	// 	exit(1);
	//
	// }
	if (*fdh != 0)
	{
		while (node->left->type == T_HERDOC)
			node = node->left;
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	if (node->left->type == T_HERDOC)
		node->left = node->left->left;
	executing(node->left, env);
	exit(0);
}

static void	handle_right_child(t_node *node, t_env *env, int *fd, int *fdh)
{
	// if (fdh != 0)
	// {
	// 	dup2(*fdh, STDOUT_FILENO);
	// 	close(fd[1]);
	// 	close(fd[0]);
	// 	executing(node->left, env);
	// 	exit(1);
	//
	// }
	(void)fdh;
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (node->right->type == T_HERDOC)
		node->right = node->right->left;
	executing(node->right, env);
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

	while (tmp && tmp->right && tmp->left)
	{
		if (tmp->type == T_PIPE)
			pipe = tmp;
		if (tmp->type == T_HERDOC)
			redir_input(tmp, env, fdh);
		if (tmp->right && tmp->right->type == T_HERDOC)
			redir_input(tmp->right, env, fdh);
		else if (tmp->left && tmp->left->type == T_HERDOC)
			redir_input(tmp->left, env, fdh);
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
	// while (tmp && tmp->right && tmp->left)
	// {
	// 	if (tmp->type == T_HERDOC)
	// 		redir_input(tmp, env, &fdh);
	// 	if (tmp->right && tmp->right->type == T_HERDOC)
	// 		redir_input(tmp->right, env, &fdh);
	// 	else if (tmp->left && tmp->left->type == T_HERDOC)
	// 		redir_input(tmp->left, env, &fdh);
	// 	tmp = tmp->right;
	// }
	pip = process_heredocs(tmp, env, &fdh);
	// printf("pip = %s\n", pip->right->cmd[0]);
	if(fdh != 0)
	{
		node = pip;
		if(ft_dup2(fdh, STDIN_FILENO) < 0)
			return ;
	}
	if (ft_pipe(fd) == -1)
		return ;
	pid1 = ft_fork();
	if (pid1 == -1)
		return ;
	if (pid1 == 0)
		handle_left_child(node, env, fd, &fdh);
	pid2 = ft_fork();
	if (pid2 == -1)
		return ;
	if (pid2 == 0)
		handle_right_child(node, env, fd, &fdh);
	close_pipes_and_wait(fd, pid1, pid2, env);
}

