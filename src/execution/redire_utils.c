/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redire_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 05:26:24 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/11 05:30:40 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_content(t_node *node, int fd, char *content, t_env *env)
{
	char	*exp_str;

	if (node->flag == 1)
		ft_putendl_fd(content, fd);
	else
	{
		exp_str = expansion_content(content, env);
		if (exp_str)
			(ft_putendl_fd(exp_str, fd), free(exp_str));
	}
}

int	check_file(t_node *node)
{
	t_node	*current;
	char	*content;

	current = node;
	while (current)
	{
		if (current->right && !current->right->cmd[0])
		{
			content = current->right->cmd[0];
			print_error("minish", content, "ambiguous redirect", NULL);
			return (0);
		}
		current = current->left;
	}
	return (1);
}
