/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:47:14 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/25 16:00:38 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ctrl_c(int signum)
{
	(void)signum;
	if (g_sig != -1)
		ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	if (g_sig != -1)
		g_sig = 1;
}

static void	set_terminal_print_off(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, 0, &term);
}

static void	do_sigint_heredoc(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", 1);
	close(0);
	g_sig = -1;
}

void	setup_signal(t_env *envp)
{
	(void)*envp;
	set_terminal_print_off();
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_heredoc(void)
{
	set_terminal_print_off();
	signal(SIGINT, do_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
