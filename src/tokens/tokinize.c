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


int is_operator(const char *str) {
    return (strncmp(str, "<<", 2) == 0 || strncmp(str, ">>", 2) == 0 ||
            *str == '<' || *str == '>' || *str == '|');
}

t_type get_operator_type(const char *str) {
    if (strncmp(str, "<<", 2) == 0) return T_HERDOC;
    if (strncmp(str, ">>", 2) == 0) return T_APPEND;
    if (*str == '<') return T_IN;
    if (*str == '>') return T_OUT;
    if (*str == '|') return T_PIPE;
    return T_WORD;  // Should never reach here
}

char *extract_word(char **input) {
    const char *start = *input;
    char quote = 0;
    
    while (**input) {
        if (!quote && is_operator(*input)) break;
        if (!quote && isspace(**input)) break;
        
        if (**input == '\'' || **input == '"') {
            if (!quote) quote = **input;
            else if (**input == quote) quote = 0;
        }
        
        (*input)++;
    }
    
    size_t len = *input - start;
    return ft_substr(start, 0, len);
}

static void sskip_spaces(char **input) {
    while (**input && isspace(**input)) (*input)++;
}

t_token *tokenize(char *input)
{
    t_token *head = NULL;
	t_token	*token;

    while (*input) {
        sskip_spaces(&input);
        if (!*input) break;

        if (is_operator(input))
		{
            t_type type = get_operator_type(input);
            char op[3] = {0};
            strncpy(op, input, type == T_HERDOC || type == T_APPEND ? 2 : 1);
            token = new_token(op, type);
            if (token) 
				token_add_back(&head, token);
            input += strlen(op);
        } else {
            char *word = extract_word(&input);
            if (word)
			{
                token = new_token(word, T_WORD);
                if (token) token_add_back(&head, token);
                free(word);
            }
        }
    }

    return head;
}

t_token *process_tokenize(char *input, t_env *env) {
    char *trimmed_input = ft_strtrim(input, " \t\n\v\f\r");
    free(input);
    if (!trimmed_input)
        return NULL;

    // Handle environment variables if needed
    if (trimmed_input[0] == '$') {
        char *env_var = get_env_var(env, trimmed_input + 1);
        free(trimmed_input);
        if (!env_var)
            return NULL;
        if (ft_strchr(env_var, '|'))
            trimmed_input = env_var;
        else {
            trimmed_input = ft_strdup(env_var);
            free(env_var);
        }
    }

    t_token *tokens = tokenize(trimmed_input);
    free(trimmed_input);
    return tokens;
}
