/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:50:02 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/24 15:06:56 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(char **args)
{
	t_list	*env;

	env = minish.env;
	if (args[1] || !is_env_var("PATH", minish.env))
	{
		print_error("env", args[1], "No such file or directory", NULL);
		return (0);
	}
	update_env_var("_", get_path_command(args[0]), minish.env);
	while (env)
	{
		if (env->content != NULL)
			printf("%s\n", (char *)env->content);
		env = env->next;
	}
	return (1);
}
