/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:14:20 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/25 23:34:32 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_gb g_minish;

int main(int argc, char **argv, char **env)
{
	char	*input;
	t_node	*tree;
	t_token	*tokens;
	int	in;
	int	out;

	(void)argv;
	(void)argc;
	init_minishell(&g_minish, env);
	while (1)
	{
		input = readline("\033[1;32mminish-1.0$ \033[0m");
		if (!input)
			break;
		add_history(input);
		tokens = tokenize_input(input);
		tree = parse_tokens(&tokens);
		out = dup(STDOUT_FILENO);
		in = dup(STDIN_FILENO);
		executing(tree);
		dup2(out, STDOUT_FILENO);
		dup2(in, STDIN_FILENO);
		free(tree);
	}
}
