/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:22:11 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/25 16:29:39 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node	*parse_cmd(t_token **tokens)
{
	t_node		*cmd;
	int		cmd_count;

	cmd = new_node(T_WORD);
	cmd_count = ft_lstsize_token(*tokens);
	cmd->cmd = malloc(sizeof(char *) * (cmd_count + 1));
	if (!cmd->cmd)
		return (NULL);
	creat_cmd(cmd, tokens, cmd_count);
	return (cmd);
}

t_node	*create_file(t_token *token)
{
	t_node			*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->cmd = malloc(sizeof(char *) * 2);
	if (!node->cmd)
		return (free(node), node = NULL, NULL);
	node->cmd[0] = expansion_file(token->value);
	node->cmd[1] = NULL;
	node->type = token->type;
	node->left = NULL;
	node->right = NULL;
	free(token);
	return (node);
}

t_node	*parse_redire(t_token **tokens)
{
	t_token		*tmp;
	t_node		*node;
	t_token		*next_token;

	if (!*tokens)
		return (NULL);
	tmp = *tokens;
	if (is_redirection((*tokens)->type))
		return (create_redire(tokens, tmp));
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if (is_redirection(next_token->type))
		{
			node = new_node((*tokens)->next->type);
			(*tokens)->next = next_token->next->next;
			node->left = parse_redire(&tmp);
			node->right = create_file((next_token->next));
			return (free(next_token->value), free(next_token), node);
		}
		*tokens = next_token;
	}
	return (parse_cmd(&tmp));
}

t_node	*build_tree(t_token **tokens)
{
	t_token		*tmp;
	t_token		*next_token;
	t_node		*node;

	tmp = *tokens;
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type == T_PIPE)
		{
			node = new_node(T_PIPE);
			(*tokens)->next = NULL;
			node->left = parse_redire(&tmp);
			node->right = build_tree(&(next_token->next));
			free(next_token->value);
			free(next_token);
			return (node);
		}
		*tokens = next_token;
	}
	return (parse_redire(&tmp));
}

static int	check_syntax(t_token *tokens)
{
	if (tokens->type == T_PIPE)
	{
		if (!tokens->next || tokens->next->type == T_WORD)
		{
			print_error("minish", "syntax error near unexpected token `|'", NULL, NULL);
			return (0);
		}
	}
	while (tokens != NULL)
	{
		if ((tokens->type >= T_IN && tokens->type <= T_HERDOC) || tokens->type == T_PIPE)
		{
			if (!tokens->next || tokens->next->type != T_WORD)
			{
				print_error("minish", "syntax error near unexpected token `newline'", NULL, NULL);
				return (0);
			}
		}
		tokens = tokens->next;
	}
	return (1);
}



t_node	*parse_tokens(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	if (!check_syntax(*tokens))
		return (clear_token(tokens), NULL);
	return (build_tree(tokens));
}
