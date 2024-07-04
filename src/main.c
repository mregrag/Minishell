/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:14:20 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/04 00:29:04 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sig = 0;

void	set_fds(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
}

void	keep_fds(int *in, int *out)
{
	*in = dup(STDIN_FILENO);
	*out = dup(STDOUT_FILENO);
}

int main(int argc, char **argv, char **env) {
    char    *input;
    t_node  *tree;
    t_env   *envp;
    t_token *tokens;
    int     in;
    int     out;

    (void)argv;
    (void)argc;

    init_env(&envp, env);
    while (1) {
        setup_signal(envp);
        keep_fds(&in, &out);  // Corrected function name
        input = readline("minish-1.0$ ");
        if (!input)
            break;
        add_history(input);
        tokens = tokenize_input(input, envp);
        if (tokens) {
            tree = parse_tokens(&tokens, envp);
            if (tree) {
                executing(tree, envp);
                free_tree(tree);  // Free tree after execution
            }
            // Free tokens after processing
        }
        g_sig = 0;
        set_fds(in, out);  // Corrected function name
        free(input);
    }
    free_env(envp);
    clear_history();
    clear_token(&tokens);
    return 0;
}

