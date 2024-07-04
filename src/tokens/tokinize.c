/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:02:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/03 23:30:01 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	separator(char **line, t_token **token_list)
{
	if (!ft_strncmp(*line, "<<", 2))
		return (add_separator(T_HERDOC, line, token_list, "<<"));
	else if (!ft_strncmp(*line, ">>", 2))
		return (add_separator(T_APPEND, line, token_list, ">>"));
	else if (!ft_strncmp(*line, "<", 1))
		return (add_separator(T_IN, line, token_list, "<"));
	else if (!ft_strncmp(*line, ">", 1))
		return (add_separator(T_OUT, line, token_list, ">"));
	else if (!ft_strncmp(*line, "|", 1))
		return (add_separator(T_PIPE, line, token_list, "|"));
	else
		return (process_word(line, token_list));
}


t_token *tokenize_input(char *input, t_env *env) {
    t_token *tokens = NULL;
    char *s = ft_strtrim(input, " \t\n\v\r\f");
    char *v = NULL;

    if (!s)
        return NULL;

    if (s[0] == '$' && is_var_in_env(env, s + 1)) {
        v = get_env_var(env, s + 1);
        if (v && ft_strchr(v, '|')) {
            token_add_back(&tokens, new_token(v, T_WORD));
            free(v);
            free(s);
            return tokens;
        }
        free(v);
    }

    char *current = s;
    while (*current) {
        if (ft_isspace(*current))
            skip_spaces(&current);
        if (!separator(&current, &tokens)) {
            clear_token(&tokens);
            free(s);
            return NULL;
        }
    }

    free(s);
    return tokens;
}
