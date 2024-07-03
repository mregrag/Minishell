/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:22:11 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/04 00:24:38 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node	*parse_cmd(t_token **tokens, t_env *env)
{
	int		cmd_count;
	t_node	*cmd;

	cmd = new_node(T_WORD);
	cmd_count = ft_lstsize_token(*tokens);
	cmd->cmd = malloc(sizeof(char *) * (cmd_count + 1));
	if (!cmd->cmd)
		return (NULL);
	creat_cmd(cmd, tokens, cmd_count, env);
	return (cmd);
}

t_node	*create_file(t_token *token, t_type type, t_env *env)
{
	t_node	*node;

	node = new_node(type);
	if (!node)
		return (NULL);
	node->cmd = malloc(sizeof(char *) * 3);
	if (!node->cmd)
		return (NULL);
	if (type == T_IN || type == T_APPEND || type == T_OUT)
		node->cmd[0] = expansion_input(token->value, env);
	else if (type == T_HERDOC)
		node->cmd[0] = expansion_dilim(token->value);
	node->cmd[1] = (NULL);
	free(token);
	return (node);
}

t_node	*parse_redire(t_token **tokens, t_env *env)
{
	t_token	*tmp;
	t_node	*node;
	t_token	*next_token;

	if (!*tokens)
		return (NULL);
	tmp = *tokens;
	if (is_redirection((*tokens)->type))
		return (create_redire(tokens, tmp, env));
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if (is_redirection(next_token->type))
		{
			node = new_node((*tokens)->next->type);
			(*tokens)->next = next_token->next->next;
			node->left = parse_redire(&tmp, env);
			node->right = create_file(next_token->next, next_token->type, env);
			free(next_token->value);
			free(next_token);
			return (node);
		}
		*tokens = next_token;
	}
	return (parse_cmd(&tmp, env));
}

t_node	*build_tree(t_token **tokens, t_env *env)
{
	t_token	*tmp;
	t_token	*next_token;
	t_node	*node;

	tmp = *tokens;
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type == T_PIPE)
		{
			node = new_node(T_PIPE);
			(*tokens)->next = NULL;
			node->left = parse_redire(&tmp, env);
			node->right = build_tree(&(next_token->next), env);
			free(next_token->value);
			free(next_token);
			return (node);
		}
		*tokens = next_token;
	}
	return (parse_redire(&tmp, env));
}

t_node	*parse_tokens(t_token **tokens, t_env *env)
{
	if (!tokens || !*tokens)
		return (NULL);
	if (!check_syntax(*tokens))
		return (NULL);
	return (build_tree(tokens, env));
}
