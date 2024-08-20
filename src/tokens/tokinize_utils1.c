/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:13:20 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/20 05:44:17 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	skip_quotes(char *line, size_t *i)
{
	char	q;

	q = line[*i];
	if (ft_strchr(line + *i + 1, q))
	{
		(*i)++;
		while (line[*i] != q)
			(*i)++;
		return (1);
	}
	return (0);
}

int	is_operator(char *str)
{
	return (!ft_strncmp(str, "<<", 2)
		|| !ft_strncmp(str, ">>", 2)
		|| *str == '<'
		|| *str == '>'
		|| *str == '|');
}

int	ft_whitespace(char *str)
{
	if (str == NULL)
		return (0);
	if (*str == '\0')
		return (1);
	while (*str)
	{
		if (ft_isspace((unsigned char)*str))
			return (1);
		str++;
	}
	return (0);
}

int	ft_isempty(char *str)
{
	if (str == NULL)
		return (1);
	while (*str)
	{
		if (!ft_isspace((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}

int	whitespace_before_equal(const char *str)
{
	char	*pos;

	pos = ft_strchr(str, '=');
	if (pos == NULL)
		return (1);
	while (str < pos)
	{
		if (ft_isspace((unsigned char)*str))
			return (1);
		str++;
	}
	return (0);
}
