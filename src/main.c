/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:20:59 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/21 06:06:24 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sig;

void	cleanup_fds(t_node *node)
{
	if (!node)
		return;
	if (node->fd_in > 2)
		close(node->fd_in);
	if (node->fd_out > 2)
		close(node->fd_out);
	cleanup_fds(node->left);
	cleanup_fds(node->right);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_node	*root;
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
		root = parse_tokens(tokens, envp);
		get_std_fds(in_out);
		Preorder_traversal(root, envp);
		(executing(root, envp), free_tree(root));
		cleanup_fds(root);
		set_std_fds(in_out[0], in_out[1]);
	}
	return (free_env(envp), 0);
}
