/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:08:23 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/10 00:19:38 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process_tokens_and_parse(char *input, t_env *env, t_node **root)
{
	t_token	*tokens;

	tokens = tokenize_input(input, env);
	*root = parse_tokens(tokens, env);
}

void	process_execution(t_node *root, t_env *env)
{
	int	in_out[2];

	get_std_fds(in_out);
	preorder_hearedoc(root, env);
	if (g_sig == 0)
		executing(root, env);
	set_std_fds(in_out[0], in_out[1]);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	*env;
	t_node	*root;

	((void)argc, (void)argv);
	initialize_enviroment(&env, envp);
	while (1)
	{
		setup_signal(env);
		input = readline("minish-1.0$ ");
		if (g_sig == 1 || g_sig == -1)
		{
			exit_status(1, env);
			g_sig = 0;
		}
		if (!input)
			handle_eof(env);
		if (*input)
			add_history(input);
		process_tokens_and_parse(input, env, &root);
		process_execution(root, env);
		cleanup_fds(root);
		free_tree(root);
	}
	free_env(env);
	return (0);
}
