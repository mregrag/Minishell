/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:50:25 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/11 07:16:19 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_node *node, t_env *env)
{
	char	cwd[PATH_MAX];

	if (node->cmd[1] && node->cmd[1][0] == '-')
	{
		print_error("minish", "pwd", "option are not supported", NULL);
		return (exit_status(1, env), 1);
	}
	getcwd(cwd, sizeof(cwd));
	ft_putendl_fd(cwd, 1);
	return (1);
}
