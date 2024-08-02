/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:08:23 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/01 21:04:32 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process_tokens_and_parse(char *input, t_env *envp, t_node **root)
{
	t_token	*tokens;

	tokens = tokenize_input(input, envp);
	*root = parse_tokens(tokens, envp);
}

void	process_execution(t_node *root, t_env *envp)
{
	int	in_out[2];

	get_std_fds(in_out);
	preorder_hearedoc(root, envp);
	if (g_sig == 0)
		executing(root, envp);
	cleanup_fds(root);
	set_std_fds(in_out[0], in_out[1]);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_env	*envp;
	t_node	*root;

	((void)argc, (void)argv);
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
		if (*input)
			add_history(input);
		process_tokens_and_parse(input, envp, &root);
		process_execution(root, envp);
		free_tree(root);
	}
	free_env(envp);
	return (0);
}
