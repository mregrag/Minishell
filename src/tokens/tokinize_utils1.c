/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:13:20 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/25 16:45:43 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_separator(char *str)
{
	if (!ft_strncmp(str, "<<", 2)
		|| *str == ' '
		|| *str == '\t'
		|| *str == '<'
		|| *str == '>'
		|| *str == '|')
		return (1);
	return (0);
}

int	skip_quotes(char *line, size_t *i)
{
	char	q;

	q = line[*i];
	if (ft_strchr(line + *i + 1, q))
	{
		(*i)++;
		while (line[*i] != q)
			(*i)++;
		(*i)++;
		return (1);
	}
	return (0);
}

void	skip_spaces(char **str)
{
	while (**str && ft_isspace(**str))
		(*str)++;
}

int	is_redirection(t_type type)
{
    return (type >= T_IN && type <= T_HERDOC);
}
