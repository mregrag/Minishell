/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:24:25 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/04 00:19:48 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	expand_cmd(t_node *node, t_env *env)
{
	int		i;
	int		count;

	count = 0;
	if (node->cmd)
		count	= ft_strlen_arg(node->cmd);
	i = 0;
	while (i < count)
	{
			node->cmd[i] = expansion_input(node->cmd[i], env);
		i++;
	}
}

void    executing(t_node *node, t_env *env)
{
    if (!node || !env)
        return;

    expand_cmd(node, env);

    if (node->type == T_WORD && node->cmd && node->cmd[0])
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
