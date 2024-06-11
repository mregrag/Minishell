/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:24:25 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/10 00:02:52 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executing(t_node *node)
{
	if (!node)
		return ;
	 //  if (node->type == T_WORD)
		// update_env_var("_", node->cmd[ft_strlen_arg(node->cmd) - 1], minish.env);
	if (node->type == T_PIPE)
		return (exec_pipe(node));
	else
		return (exec_cmd(node));
}
