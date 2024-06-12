/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 21:45:53 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/11 20:50:14 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_dollar(char *str, size_t *i)
{
	size_t	start;
	char	*var;
	char	*val;

	(*i)++;
	if (ft_isdigit(str[*i]) || str[*i] == '@')
		return ((*i)++, NULL);
	else if (str[*i] == '?')
		return ((*i)++, ft_itoa(minish.exit_status));
	else if (!(ft_isalnum(str[*i]) || str[*i] == '_'))
		return ("$");
	start = *i;
	while ((ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	val = ft_strtrim(ft_getenv(var), " \t\n\v\r\f");
	if (!val)
		return (free(var), NULL);
	return (free(var), val);
}

char	*expand_cmd(char *str)
{
	char	*ret;
	size_t	i;

	ret = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			ret = ft_strjoin(ret, handle_sq(str, &i));
		else if (str[i] == '"')
			ret = ft_strjoin(ret, handle_dq(str, &i));
		if (str[i] == '$')
			ret = ft_strjoin(ret, handle_dollar(str, &i));
		else
			ret = ft_strjoin(ret, handle_str(str, &i));
	}
	return (remov_quotes(ret));
}

char	*expand_heredoc(char *str)
{
	char	*ret;
	size_t	i;

	ret = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			ret = ft_strjoin(ret, handle_sq(str, &i));
		else if (str[i] == '"')
			ret = ft_strjoin(ret, handle_dq(str, &i));
		else if (str[i] == '$')
			ret = ft_strjoin(ret, handle_dollar(str, &i));
		else
			ret = ft_strjoin(ret, handle_str(str, &i));
	}
	return (ret);
}

char	*expand_file(char *str)
{
	char	*ret;
	size_t	i;

	ret = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			ret = ft_strjoin(ret, handle_sq(str, &i));
		else if (str[i] == '"')
			ret = ft_strjoin(ret, handle_dq(str, &i));
		else
			ret = ft_strjoin(ret, handle_str(str, &i));
	}
	return (ret);
}
