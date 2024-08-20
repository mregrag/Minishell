/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:05:33 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/20 05:41:51 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_quotes(char *line)
{
	size_t	i;

	i = 0;
	while ((line)[i])
	{
		if (ft_isquotes(line[i]) && !skip_quotes(line, &i))
			return (print_error("minish", "unexpected EOF `", NULL, NULL), 0);
		else
			i++;
	}
	return (1);
}

t_type	get_operator_type(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0)
		return (T_HERDOC);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (T_APPEND);
	if (*str == '<')
		return (T_IN);
	if (*str == '>')
		return (T_OUT);
	if (*str == '|')
		return (T_PIPE);
	return (T_CMD);
}

int	check_operators(char *str)
{
	while (*str)
	{
		if (is_operator(str))
			return (1);
		str++;
	}
	return (0);
}

void	skip_spaces(char **str)
{
	while (**str && ft_isspace(**str))
		(*str)++;
}

int	count_quotes(const char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
		return 0;
	while (*str == '"' || *str == '\'')
	{
		count++;
		str++;
	}
	return (count);
}
