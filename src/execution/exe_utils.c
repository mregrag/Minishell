/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:11:01 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/09 17:12:58 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		(print_error("minish", "fork", strerror(errno), NULL), exit_status(1));
	return (pid);
}

int	ft_pipe2(int ends[2])
{
	int	ret;

	ret = pipe(ends);
	if (!ret)
		return (0);
	print_error("minish", "pipe", strerror(errno), NULL);
	exit_status(1);
	return (-1);
}

int	ft_dup_2(int filde1, int filde2)
{
	int	fd;

	fd = dup2(filde1, filde2);
	if (fd != -1)
		return (fd);
	print_error("minish", "dup2", strerror(errno), NULL);
	exit_status(1);
	return (-1);
}

