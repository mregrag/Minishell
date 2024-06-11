/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:14:20 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/11 19:18:19 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_gb minish;

int main(int argc, char **argv, char **env)
{
	char *input;
	t_node *tree;
	t_token *tokens;
	int	in;
	int	out;

	(void)argv;
	(void)argc;

	init_minishell(&minish, env);
	while (1)
	{
		input = readline("\033[1;32mminish-1.0$ \033[0m");
		if (!input)
			break;
		add_history(input);
		tokens = tokenize_input(input);
		tree = parse_tokens(&tokens);
		// printf("type left  = %d\n", tree->left->type);
		// printf("type right = %d\n", tree->right->type);
		out = dup(STDOUT_FILENO);
		in = dup(STDIN_FILENO);
		executing(tree);
		dup2(out, STDOUT_FILENO);
		dup2(in, STDIN_FILENO);
		close(in);
		close(out);
		free(tree);
	}
}
