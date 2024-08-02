/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:45:05 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/01 00:02:11 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_total_args(char **original_cmd)
{
	int		i;
	int		total;
	char	**split_arg;

	total = 0;
	i = 0;
	while (original_cmd[i])
	{
		split_arg = ft_split(original_cmd[i], ' ');
		if (!split_arg)
			return (-1);
		total += ft_strlen_arg(split_arg);
		ft_free_array(split_arg);
		i++;
	}
	return (total);
}

static char	**allocate_new_cmd(int total_args)
{
	char	**new_cmd;

	new_cmd = (char **)malloc(sizeof(char *) * (total_args + 1));
	if (!new_cmd)
		return (NULL);
	new_cmd[total_args] = NULL;
	return (new_cmd);
}

static int	add_split_args(char **new_cmd, char **split_arg, int *k)
{
	int	j;

	j = 0;
	while (split_arg[j])
	{
		new_cmd[*k] = ft_strdup(split_arg[j]);
		if (!new_cmd[*k])
			return (0);
		(*k)++;
		j++;
	}
	return (1);
}

static int	process_original_cmd(char **new_cmd, char **original_cmd)
{
	char	**split_arg;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (original_cmd[i])
	{
		split_arg = ft_split(original_cmd[i], ' ');
		if (!split_arg)
			return (0);
		if (!add_split_args(new_cmd, split_arg, &k))
		{
			ft_free_array(split_arg);
			return (0);
		}
		ft_free_array(split_arg);
		i++;
	}
	return (1);
}

char	**prepare_command(char **original_cmd)
{
	char	**new_cmd;
	int		total_args;

	total_args = count_total_args(original_cmd);
	if (total_args == -1)
		return (NULL);
	new_cmd = allocate_new_cmd(total_args);
	if (!new_cmd)
		return (NULL);
	if (!process_original_cmd(new_cmd, original_cmd))
	{
		ft_free_array(new_cmd);
		return (NULL);
	}
	return (new_cmd);
}
