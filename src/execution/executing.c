/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:24:25 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/22 21:53:17 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executing(t_node *node, t_env *env)
{
	struct termios	term;

	if (!node || !env)
		return ;
	tcgetattr(STDIN_FILENO, &term);
	if (is_redirection(node->type) && handle_redirections(node, env))
		while (node && node->left)
			node = node->left;
	if (execute_builtin(node, env))
		return ;
	if (node->type == T_PIPE)
		execute_pipe(node, env);
	execute_command(node, env);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
