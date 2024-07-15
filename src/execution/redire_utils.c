/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redire_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 05:26:24 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/15 07:30:38 by mregrag          ###   ########.fr       */
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

t_node	*find_heredoc(t_node *node)
{
	t_node	*current;

	current = node;
	while (current && current->left)
	{
		if (current->left->type  == T_HERDOC || current->right->type == T_HERDOC)
			return (current);
		current = current->right;
	}
	current = node;
	while (current && current->left)
	{
		if (current->right->type  == T_HERDOC)
			return (current);
		current = current->left;
	}
	return (NULL);
}
int	ft_open_input(char *file)
{
	int	fd;

	if (!file)
	{
		print_error("minish", "ambiguous redirect", NULL, NULL);
		return (-1);
	}
	fd = open(file, O_RDONLY, 00644);
	if (fd == -1)
		print_error("minish", (char *)file, strerror(errno), NULL);
	return (fd);
}

int	ft_open_output(char *file)
{
	int	fd;

	if (!file)
	{
		print_error("minish", "ambiguous redirect", NULL, NULL);
		return (-1);
	}
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd == -1)
		print_error("minish", (char *)file, strerror(errno), NULL);
	return (fd);
}

int	ft_open_append(char *file)
{
	int	fd;

	if (!file)
	{
		print_error("minish", "ambiguous redirect", NULL, NULL);
		return (-1);
	}
	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 00644);
	if (fd == -1)
		print_error("minish", (char *)file, strerror(errno), NULL);
	return (fd);
}
