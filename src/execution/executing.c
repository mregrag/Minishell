/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:24:25 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/10 21:40:58 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executing(t_node *node, t_env *env)
{
	if (!node || !env)
		return ;
	if (node->type == T_WORD && execute_builtin(node, env))
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
		exec_cmd(node, env);
}
