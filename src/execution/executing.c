/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:24:25 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/08 21:29:48 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    executing(t_node *node, t_env *env)
{
    if (!node || !env)
        return;

    if (node->type == T_WORD && node->cmd)
    {
        int last_arg = ft_strlen_arg(node->cmd) - 1;
        if (last_arg >= 0)
            set_env_var(env, "_", node->cmd[last_arg]);
    }
    if (node->type == T_PIPE)
        exec_pipe(node, env);
    else
        exec_cmd(node, env);
}
