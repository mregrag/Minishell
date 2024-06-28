/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:14:20 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/28 22:43:40 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_gb g_minish;

void	term_attr(struct termios *att)
{
	if (isatty(STDIN_FILENO) && tcgetattr(STDIN_FILENO, att))
		perror("termios");
}

int main(int argc, char **argv, char **env)
{
    char    *input;
    t_node  *tree;
    t_node	*minish_env;
    t_token *tokens;
    int     in;
    int     out;

    struct termios original_termios;
    tcgetattr(STDIN_FILENO, &original_termios);

    (void)argv;
    (void)argc;

    minish_env = init_minishell(env, &in, &out);
    while (1)
    {
        input = readline("\033[1;32mminish-1.0$ \033[0m");
        if (!input)
            break;
        add_history(input);
	term_attr(&original_termios);
        tokens = tokenize_input(input, minish_env);
        tree = parse_tokens(&tokens, minish_env->env);
        executing(tree);
	if (isatty(STDIN_FILENO) && tcsetattr(0, TCSANOW, &original_termios))
		perror("termios");
	reset_in_out(in, out);
    }
    return 0;
}
