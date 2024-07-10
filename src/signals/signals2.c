/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:38:35 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/10 23:58:33 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	block_signals(struct sigaction *sa_ignore)
{
	sigaction(SIGINT, sa_ignore, NULL);
	sigaction(SIGQUIT, sa_ignore, NULL);
}

void	restore_signals(struct sigaction *sa_default)
{
	sigaction(SIGINT, sa_default, NULL);
	sigaction(SIGQUIT, sa_default, NULL);
}

void	signal_handlers(struct sigaction *sa_ig, struct sigaction *sa_def)
{
	sa_ig->sa_handler = SIG_IGN;
	sigemptyset(&sa_ig->sa_mask);
	sa_ig->sa_flags = 0;
	sa_def->sa_handler = SIG_DFL;
	sigemptyset(&sa_def->sa_mask);
	sa_def->sa_flags = 0;
}
