/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:49:43 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/05 15:25:31 by mregrag          ###   ########.fr       */
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
		else if (tokens->type == T_WORD)
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
