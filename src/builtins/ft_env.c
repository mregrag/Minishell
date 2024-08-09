/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:50:02 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/09 21:09:35 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_node *node, t_env *env)
{
	if (ft_strlen_arg(node->cmd) > 1)
	{
		print_error("env", node->cmd[1], "No such file or directory", NULL);
		return (exit_status(127, env), 1);
	}
	print_env(env);
	set_env_var(env, "_", node->cmd[ft_strlen_arg(node->cmd) - 1]);
	return (1);
}
