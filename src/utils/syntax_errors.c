/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:49:43 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/13 08:18:13 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_redir_errors(t_token *token)
{
	if (!token->next)
		return (1);
	if (token->next->type == T_PIPE)
		return (2);
	if (token->next->type != T_CMD)
		return (3);
	return (0);
}

static int	check_token(t_token *token, int had_pipe)
{
	if (token->type == T_PIPE)
	{
		if (!token->next || had_pipe)
			return (2);
	}
	else if (is_redirection(token->type))
		return (check_redir_errors(token));
	return (0);
}

static int	check_syntax_recursive(t_token *token, int had_pipe)
{
	int	error;

	if (!token)
	{
		if (had_pipe)
			return (1);
		return (0);
	}
	error = check_token(token, had_pipe);
	if (error)
		return (error);
	if (token->type == T_PIPE)
		return (check_syntax_recursive(token->next, 1));
	if (is_redirection(token->type))
		return (check_syntax_recursive(token->next->next, 0));
	return (check_syntax_recursive(token->next, 0));
}

static void	print_errors(int error_code, char *value)
{
	if (error_code == 1)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else if (error_code == 2)
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	else if (error_code == 3)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(value, 2);
		ft_putstr_fd("'\n", 2);
	}
}

int	check_syntax(t_token *tokens)
{
	int	error_code;

	if (tokens && tokens->type == T_PIPE)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	error_code = check_syntax_recursive(tokens, 0);
	if (error_code)
	{
		if (tokens->next)
			print_errors(error_code, tokens->next->value);
		else
			print_errors(error_code, NULL);
		return (1);
	}
	return (0);
}
