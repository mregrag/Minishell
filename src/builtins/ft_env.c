/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:50:02 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/03 22:19:31 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_node *node, t_env *env)
{
	char	*path;

	path = get_path(node->cmd[0], env);
	if (node->cmd[1] || !is_var_in_env(env, "PATH"))
	{
		print_error("env", node->cmd[1], "No such file or directory", NULL);
		return (1);
	}
	if (path)
	{
		set_env_var(env, "_", path);
		free(path);
	}
	print_env(env);
	return (1);
}
