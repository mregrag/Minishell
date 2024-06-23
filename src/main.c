/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:14:20 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/23 18:59:39 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_gb minish;

int main(int argc, char **argv, char **env)
{
	char *input;
	t_node *tree;
	t_token *tokens;

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
		executing(tree);
		set_fd(minish.input, minish.output);
		free(tree);
	}
}
