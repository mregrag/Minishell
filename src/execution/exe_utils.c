/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:11:01 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/23 18:37:39 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pipe(int fd[2])
{
	int	ret;

	ret = pipe(fd);
	if (!ret)
		return (0);
	print_error("minish", "pipe", strerror(errno), NULL);
	exit_status(1);
	return (-1);
}

int	ft_dup2(int fd1, int fd2)
{
	int	ret;

	ret = dup2(fd1, fd2);
	if (ret != -1)
		return (ret);
	print_error("minish", "dup2", strerror(errno), NULL);
	exit_status(1);
	return (-1);
}

int	ft_close(int fd)
{
	int	ret;

	ret = close(fd);
	if (!ret)
		return (0);
	print_error("minish", "close", strerror(errno), NULL);
	exit_status(1);
	return (-1);
}
