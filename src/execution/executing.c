/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:24:25 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/15 20:02:44 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executing(t_node *node, t_env *env)
{
	struct termios	term;

	if (!node || !env)
		return ;
	tcgetattr(STDIN_FILENO, &term);
	if (node->type == T_CMD && execute_builtin(node, env))
		return ;
	if (is_redirection(node->type))
	{
		if (redirections(node, env))
			while (node->left)
				node = node->left;
	}
	if (node->type == T_PIPE)
		exec_pipe(node, env);
	else
		execute_command(node, env);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
