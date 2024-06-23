/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:50:25 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/07 22:50:24 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
}
