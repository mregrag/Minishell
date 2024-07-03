/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:47:14 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/03 18:58:31 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_h(int sigN)
{
	extern int	g_sig;

	if (g_sig == 0)
	{
		(void)sigN;
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}
void	sig_ign(void)
{
	if (signal(SIGINT, sigint_h) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("shell -- signals err");
}

void	sig_allow(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR
		|| signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		perror("shell -- signals err");
}

void	heredoc_h(int n)
{
	extern int	g_sig;

	(void)n;
	g_sig = 2;
	close(STDIN_FILENO);
}



