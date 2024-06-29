/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 21:45:53 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/29 22:14:24 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expansion_input(char *str, t_node *node)
{
	size_t	i;
	char	*ret;

	ret = strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			ret = handle_single_quotes(ret, str, &i);
		else if (str[i] == '"')
			ret = handle_double_quotes(ret, str, &i, node);
		else if (str[i] == '$')
			ret = handle_dollar(ret, str, &i, node);
		else
			ret = handle_normal(ret, str, &i);
	}
	return (remov_quotes(ret));
}
