/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:14:20 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/29 18:58:37 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_gb g_minish;

int main(int argc, char **argv, char **env)
{
    char    *input;
    t_node  *tree;
    t_node	*minish_env;
    t_token *tokens;
    int	in;
    int	out;


    (void)argv;
    (void)argc;

    minish_env = init_minishell(env);
    while (1)
    {
        input = readline("\033[1;32mminish-1.0$ \033[0m");
        if (!input)
            break;
        add_history(input);
        tokens = tokenize_input(input, minish_env);
        tree = parse_tokens(&tokens, minish_env->env);
	out = dup(STDOUT_FILENO);
	in = dup(STDIN_FILENO);
	executing(tree);
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	close(in);
	close(out);
    }
    return 0;
}
