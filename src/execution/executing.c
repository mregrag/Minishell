/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:24:25 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/03 14:40:53 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executing(t_node *node, t_env *env)
{
	struct termios	term;

	if (!node || !env)
		return ;
	tcgetattr(STDIN_FILENO, &term);
	if (!handle_redirections(&node, env))
		return ;
	if (execute_builtin(node, env))
		return ;
	if (node->type == T_PIPE)
		execute_pipe(node, env);
	execute_command(node, env);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
