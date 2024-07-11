/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:49:43 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/11 18:49:07 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	syntax_error(char *message, t_token *token)
{
	if (token && token->value)
		print_error("minish", ERRTOKEN, token->value, NULL);
	else
		print_error("minish", "syntax error", message, NULL);
	return (0);
}

int	check_syntax(t_token *tokens)
{
	int	after_pipe;
	int	after_redirection;

	after_pipe = false;
	after_redirection = false;
	while (tokens)
	{
		if (tokens->type == T_PIPE)
		{
			if (after_pipe || after_redirection)
				return (syntax_error("unexpected token `|'", tokens));
			after_pipe = true;
			after_redirection = false;
		}
		else if (is_redirection(tokens->type))
		{
			if (after_redirection)
				return (syntax_error("unexpected token", tokens));
			after_redirection = true;
			after_pipe = false;
		}
		else if (tokens->type == T_CMD)
		{
			after_pipe = false;
			after_redirection = false;
		}
		if (!tokens->next && (after_pipe || after_redirection))
			return (syntax_error("unexpected token `newline'", NULL));
		tokens = tokens->next;
	}
	return (1);
}
// static int	syntax_error(char *message, t_token *token)
// {
// 	if (token && token->value)
// 		print_error("minish", "syntax error", token->value, NULL);
// 	else
// 		print_error("minish", "syntax error", message, NULL);
// 	return (0);
// }
//
// int	check_syntax(t_token *tokens)
// {
// 	bool	expect_cmd;
//
// 	expect_cmd = true;
// 	while (tokens)
// 	{
// 		if (tokens->type == T_PIPE || is_redirection(tokens->type))
// 		{
// 			if (expect_cmd)
// 				return (syntax_error("unexpected token", tokens));
// 			expect_cmd = true;
// 		}
// 		else if (tokens->type == T_CMD)
// 			expect_cmd = false;
// 		if (!tokens->next && expect_cmd)
// 			return (syntax_error("unexpected token `newline'", NULL));
// 		tokens = tokens->next;
// 	}
// 	return (1);
// }
