/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:50:02 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/28 19:59:00 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_node *node)
{
	t_list	*env;

	env = node->env;
	if (node->cmd[1] || !ft_getenv("PATH", node->env))
	{
		print_error("env", node->cmd[1], "No such file or directory", NULL);
		return (0);
	}
	update_env_var("_", get_path(node->cmd[0], node->env), node);
	while (env)
	{
		if (env->content != NULL && !ft_strchr(env->content, '?'))
			printf("%s\n", (char *)env->content);
		env = env->next;
	}
	return (1);
}
