/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:24:25 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/08 18:44:26 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executing(t_node *node, t_env *env)
{
	struct termios	term;
	if (!node || !env)
		return ;

	tcgetattr(STDIN_FILENO, &term);
	if (!execute_redirections(&node, env))
		return ;
	else if (execute_builtin(node, env))
		return ;
	else if (node->type == T_PIPE)
		execute_pipe(node, env);
	else if (node->type == T_CMD)
		execute_command(node, env);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
