/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:24:25 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/03 19:57:20 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	creat_cmd(t_node *node, t_token **tokens, int count)
{
	int		i;
	t_token	*tmp;

	i = 0;
	while (i < count)
	{
		node->cmd[i] = (*tokens)->value;
		tmp = *tokens;
		*tokens = (*tokens)->next;
		i++;
	}
	node->cmd[count] = NULL;
}

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
