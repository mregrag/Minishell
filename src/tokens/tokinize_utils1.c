/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:13:20 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/05 19:00:37 by mregrag          ###   ########.fr       */
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

void	ft_skip_spaces(char **str)
{
	while (**str && ft_isspace(**str))
		(*str)++;
}

int	ft_is_quote(char c)
{
	return (c == 39 || c == 34);
}

void	quotes_error(char c)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\n', 2);
	minish.exit_status = 258;
}
