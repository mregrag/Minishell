/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:22:11 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/08 15:39:00 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node	*parse_command(t_token *tokens, t_env *env)
{
	t_node	*node;
	int		count;

	node = new_node(T_CMD);
	count = ft_lstsize_token(tokens);
	node->cmd = malloc(sizeof(char *) * (count + 1));
	if (!node->cmd)
		malloc_error();
	fill_cmd(node, tokens, env, count);
	return (node);
}

t_node	*parse_file(t_token *token, t_type type, t_env *env)
{
	t_node	*node;

	node = new_node(type);
	node->cmd = malloc(sizeof(char *) * 2);
	if (!node->cmd)
		malloc_error();
	if (type == T_IN || type == T_APPEND || type == T_OUT)
		node->cmd[0] = expansion_input(token->value, env);
	else if (type == T_HERDOC)
		node->cmd[0] = ft_strdup(token->value);
	node->cmd[1] = NULL;
	return (free_token(token), node);
}

t_node	*parse_redirection(t_token *tokens, t_env *env)
{
	t_token	*tmp;
	t_node	*node;
	t_token	*next_token;

	if (!tokens)
		return (NULL);
	tmp = tokens;
	if (is_redirection(tokens->type))
		return (create_redire(tokens, tmp, env));
	while (tokens && (tokens)->next)
	{
		next_token = tokens->next;
		if (is_redirection(next_token->type))
		{
			node = new_node(next_token->type);
			tokens->next = next_token->next->next;
			node->left = parse_redirection(tmp, env);
			node->right = parse_file(next_token->next, next_token->type, env);
			return (free_token(next_token), node);
		}
		tokens = next_token;
	}
	return (parse_command(tmp, env));
}

t_node	*parse_expression(t_token *tokens, t_env *env)
{
	t_token	*tmp;
	t_token	*next_token;
	t_node	*node;

	tmp = tokens;
	while (tokens && tokens->next)
	{
		next_token = tokens->next;
		if (next_token->type == T_PIPE)
		{
			node = new_node(T_PIPE);
			tokens->next = NULL;
			node->left = parse_redirection(tmp, env);
			node->right = parse_expression(next_token->next, env);
			return (free_token(next_token), node);
		}
		tokens = next_token;
	}
	return (parse_redirection(tmp, env));
}

t_node	*parse_tokens(t_token *tokens, t_env *env)
{
	if (!tokens)
		return (NULL);
	if (check_syntax(tokens))
		return (clear_tokens(&tokens), exit_status(258, env), NULL);
	return (parse_expression(tokens, env));
}
