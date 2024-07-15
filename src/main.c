/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:20:59 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/15 20:18:59 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sig;

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_node	*tree;
	t_env	*envp;
	t_token	*tokens;
	int		in_out[2];

	((void)argv, (void)argc);
	init_env(&envp, env);
	while (1)
	{
		setup_signal(envp);
		input = readline("minish-1.0$ ");
		if (g_sig == 1 || g_sig == -1)
			(exit_status(1, envp), g_sig = 0);
		if (!input)
			handle_eof(envp);
		if (*input)
			add_history(input);
		tokens = tokenize_input(input, envp);
		tree = parse_tokens(tokens, envp);
		get_std_fds(in_out);
		(executing(tree, envp), free_tree(tree));
		set_std_fds(in_out[0], in_out[1]);
	}
	return (free_env(envp), 0);
}
