/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:24:25 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/02 00:10:20 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executing(t_node *node)
{
	if (!node)
		return ;
	if (node->type == T_WORD && node->cmd[0])
		set_env_var(node->env, "_", node->cmd[ft_strlen_arg(node->cmd) - 1]);
	if (node->type == T_PIPE)
		return (exec_pipe(node));
	else
		return (exec_cmd(node));
}
