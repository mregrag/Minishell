/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:14:20 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/10 23:53:53 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sig = 0;

void ctl_d(t_env   *envp)
{
	char    *status;

	printf("exit\n");
	status = get_env_var(envp, "?");
	exit(ft_atoi(status));
}

void	reset_file_descriptors(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
}


int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_node	*tree;
	t_env	*envp;
	t_token	*tokens;
	int		in_out[2];
	struct termios	term;

	((void)argv, (void)argc);
	tcgetattr(STDIN_FILENO, &term);
	init_env(&envp, env);
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
			ctl_d(envp);
		add_history(input);
		tokens = process_tokenize(input, envp);
		tree = parse_tokens(&tokens, envp);
		in_out[0] = dup(STDIN_FILENO);
		in_out[1] = dup(STDOUT_FILENO);
		(executing(tree, envp), free_tree(tree));
		reset_file_descriptors(in_out[0], in_out[1]);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	return (free_env(envp), 0);
}
