/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:14:20 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/08 18:58:53 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sig = 0;

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_node	*tree;
	t_env	*envp;
	t_token	*tokens;
	int		original_stdin;
	int		original_stdout;

	(void)argv;
	(void)argc;
	init_env(&envp, env);
	while (1)
	{
		setup_signal(envp);
		input = readline("minish-1.0$ ");
		if (!input)
			break ;
		add_history(input);
		tokens = process_tokenize(input, envp);
		tree = parse_tokens(&tokens, envp);
		original_stdin = dup(STDIN_FILENO);
		original_stdout = dup(STDOUT_FILENO);
		executing(tree, envp);
		free_tree(tree);
		g_sig = 0;
		dup2(original_stdin, STDIN_FILENO);
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdin);
		close(original_stdout);
	}
	free_env(envp);
	return (0);
}
