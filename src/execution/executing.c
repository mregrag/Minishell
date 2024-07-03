/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:24:25 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/03 21:27:28 by mkoualil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executing(t_node *node, t_env *env)
{
	if (!node)
		return ;
	if (node->type == T_WORD && node->cmd[0])
		set_env_var(env, "_", node->cmd[ft_strlen_arg(node->cmd) - 1]);
	if (node->type == T_PIPE)
		return (exec_pipe(node, env));
	else
		return (exec_cmd(node, env));
}
