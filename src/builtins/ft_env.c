/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:50:02 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/01 22:14:02 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_node *node)
{
	t_list	*env;

	env = node->env->env;
	if (node->cmd[1] || !get_env_var(node->env, "PATH"))
	{
		print_error("env", node->cmd[1], "No such file or directory", NULL);
		return (1);
	}
	set_env_var(node->env, "_", get_path(node->cmd[0], node->env));
	print_env(node->env);
	return (1);
}
