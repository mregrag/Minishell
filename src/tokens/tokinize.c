/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokinize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:02:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/05 15:54:38 by mregrag          ###   ########.fr       */
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



t_token	*tokenize_input(char *input, t_env *env)
{
	t_token	*tokens;
    (void)env;
	tokens = NULL;
	while (*input)
	{
		if (ft_isspace(*input))
			skip_spaces(&input);
		if (!separator(&input, &tokens))
			return (clear_token(&tokens), NULL);
	}
	return (tokens);
}

t_token *process_tokenize(char *input, t_env *env)
{
    char *trimmed_input;
    char *env_var;
    t_token *tokens;

    (void)env;
    trimmed_input = ft_strtrim(input, " \t\n\v\f\r");
    free(input);
    if (!trimmed_input)
        return (NULL);
    if (trimmed_input[0] == '$')
    {
        env_var = get_env_var(env, trimmed_input + 1);
        free(trimmed_input);
        if (!env_var)
            return (NULL);
        if (ft_strchr(env_var, '|'))
            trimmed_input = env_var;
    }
    tokens = tokenize_input(trimmed_input, env);
    free(trimmed_input);
    return (tokens);
}
