/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 04:11:35 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/21 18:53:07 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	process_heredoc_content(t_node *node, int *fd_heredoc, t_env *env)
{
	char	*content;
	char	*dilim;

	dilim = expansion_dilim(node->cmd[0]);
	while (1)
	{
		content = readline("> ");
		if (!ttyname(0))
			return (free(content), free(dilim), -1);
		if (!content)
			return (free(dilim), 0);
		if (!dilim || !ft_strcmp(content, dilim))
		{
			(free(content));
			break ;
		}
		heredoc_content(node, fd_heredoc[1], content, env);
		free(content);
	}
	return (free(dilim), 0);
}

int	heredoc(t_node *node, t_env *env)
{
	int	fd_heredoc[2];

	if (ft_pipe(fd_heredoc) < 0)
		return (-1);
	set_signal_heredoc();
	node->flag = ft_strchr(node->cmd[0], '\'') || ft_strchr(node->cmd[0], '"');
	if (process_heredoc_content(node, fd_heredoc, env) < 0)
	{
		close(fd_heredoc[0]);
		close(fd_heredoc[1]);
		return (-1);
	}
	close(fd_heredoc[1]);
	return (fd_heredoc[0]);
}
