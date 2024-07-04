/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:50:47 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/03 23:33:42 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void	export_list(t_list *env)
{
	char	*content;

	while (env)
	{
		content = (char *)env->content;
		if (content[0] != '?' && content[0] != '_')
			printf("declare -x %s\"\n", content);
		env = env->next;
	}
}

static int	check_var(const char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	find_char_index(const char *str, char c)
{
	int	index;

	index = 0;
	if (!str)
		return (-1);
	while (str[index] != '\0')
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	return (-1);
}
void add_arg_to_env(char *argv, t_env *env) {
    int index = find_char_index(argv, '=');
    char *var = ft_substr(argv, 0, index);
    char *trimmed_var = ft_strtrim(var, "+");
    free(var);  // Free the initial substring result

    char *value = ft_substr(argv, index + 1, ft_strlen(argv) - index);

    if (ft_issamechar(value, '$')) {
        free(value);  // Free previous value before reassigning
        value = ft_itoa(getpid());
    }

    char *existing_value = get_env_var(env, trimmed_var);
    if (existing_value && !ft_strchr(argv, '+')) {
        set_env_var(env, trimmed_var, value);
    } else if (existing_value && argv[index - 1] == '+') {
        char *new_value = ft_strjoin(existing_value, value);
        free(value);  // Free the original value before reassigning
        set_env_var(env, trimmed_var, new_value);
        free(new_value);  // Free the joined string after setting it
    } else if (ft_strchr(argv, '=')) {
        set_env_var(env, trimmed_var, value);
    }

    free(existing_value);  // Free memory allocated by get_env_var
    free(trimmed_var);
    free(value);
}


int	ft_export(t_node *node, t_env *env)
{
	char	**argv;
	t_list	*envp;

	envp = env->env;
	argv = node->cmd;
	if (!argv[1])
		return (export_list(envp), 1);
	while (*(++argv))
	{
		if (!check_var(*argv))
		{
			print_error("minish", "export", *argv, "not a valid identifier");
			set_env_var(env, "?", "1");
		}
		else
			add_arg_to_env(*argv, env);
	}
	return (1);
}
