/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:05:33 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/26 11:20:38 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*extract_word(char **input)
{
	char	*start;
	size_t	len;
	char	quote;

	quote = 0;
	start = *input;
	while (**input)
	{
		if (!quote && is_operator(*input))
			break ;
		if (!quote && ft_isspace(**input))
			break ;
		if (ft_isquotes(**input))
		{
			if (!quote)
				quote = **input;
			else if (**input == quote)
				quote = 0;
		}
		(*input)++;
	}
	len = *input - start;
	return (ft_substr(start, 0, len));
}

int	check_quotes(char **line)
{
	size_t	i;

	i = 0;
	while ((*line)[i])
	{
		if (ft_isquotes((*line)[i]) && !skip_quotes(*line, &i))
			return (print_error("minish", "unexpected EOF `", NULL, NULL), 0);
		else
			i++;
	}
	return (1);
}

int	is_operator(char *str)
{
	if (!str)
		return (0);
	return (!ft_strncmp(str, "<<", 2)
		|| !ft_strncmp(str, ">>", 2)
		|| *str == '<'
		|| *str == '>'
		|| *str == '|');
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
