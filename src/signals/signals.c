/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:47:14 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/03 21:32:52 by mkoualil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
static void	ctrl_c()
{
	extern int g_sig;

	// g_minish.exit_status = 1;
	g_sig = 1;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();

}

void	setup_signal(t_env *envp)
{
	extern int g_sig;

	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	if (g_sig == 1)
		exit_status(1, envp);
}
