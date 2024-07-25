/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:08:23 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/25 16:16:09 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	process_command(char *input, t_env *envp, int in_out[2])
{
	t_node	*root;
	t_token	*tokens;

	if (*input)
		add_history(input);
	tokens = tokenize_input(input, envp);
	root = parse_tokens(tokens, envp);
	get_std_fds(in_out);
	preorder_traversal_hearedoc(root, envp);
	preorder_traversal_input_output(root);
	if (g_sig == 0)
		executing(root, envp);
	cleanup_fds(root);
	free_tree(root);
	set_std_fds(in_out[0], in_out[1]);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_env	*envp;
	int		in_out[2];

	envp = NULL;
	if (argc == 1 && !argv[1])
	{
		initialize_enviroment(&envp, env);
		while (1)
		{
			setup_signal(envp);
			input = readline("minish-1.0$ ");
			if (g_sig == 1 || g_sig == -1)
			{
				exit_status(1, envp);
				g_sig = 0;
			}
			if (!input)
				handle_eof(envp);
			process_command(input, envp, in_out);
		}
	}
	return (free_env(envp), 0);
}
