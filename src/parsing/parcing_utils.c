/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:23:34 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/09 21:38:31 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

t_node	*new_node(t_type type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		malloc_error();
	node->type = type;
	node->cmd = NULL;
	node->left = NULL;
	node->right = NULL;
	node->fd_in = 0;
	node->fd_out = 1;
	return (node);
}

void	free_tree(t_node *node)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	if (node->cmd)
	{
		while (node->cmd[i])
		{
			free(node->cmd[i]);
			i++;
		}
		free(node->cmd);
	}
	free_tree(node->left);
	free_tree(node->right);
	free(node);
}

// static int is_espace(char *str)
// {
// 	char *s = str;
// 	size_t count = 0;
// 	while (*str)
// 	{
// 		if (*str != ' ')
// 			count++;
// 		str++;
// 	}
// 	if (count == ft_strlen(s))
// 		return -1;
// 	return 0;
// }

void	fill_cmd(t_node *node, t_token *tokens, t_env *env, int count)
{
	int		i;
	int		j;
	char	*expanded;
	char	*trim_expand;
	t_token	*tmp;

	i = 0;
	j = 0;
	while (i < count)
	{
		expanded = expansion_input(tokens->value, env);

		if (expanded != NULL)
		{

			printf("expanded %s\n", expanded);
			trim_expand = ft_strtrim(expanded, " \t\n\v\f\r");
			node->cmd[j++] = trim_expand;
// ;			if (is_espace(expanded) == 0)
// 			{
// 				printf("expanded %s\n", expanded);
// 				trim_expand = ft_strtrim(expanded, " \t\n\v\f\r");
// 				node->cmd[j++] = trim_expand;
// 			}

		}
		tmp = tokens;
		tokens = tokens->next;
		(free_token(tmp), free(expanded));
		i++;
	}
	node->cmd[j] = NULL;
}

t_node	*create_redire(t_token *tokens, t_token *tmp, t_env *env)
{
	t_node	*node;

	node = new_node(tokens->type);
	tokens = tokens->next->next;
	node->left = parse_redirection(tokens, env);
	node->right = parse_file(tmp->next, tmp->type, env);
	free_token(tmp);
	return (node);
}
