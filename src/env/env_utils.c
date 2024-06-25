/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:25:14 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/25 16:14:44 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_getenv(char *key)
{
	int		i;
	t_list	*envp;
	char	*tmp;
	char	*value;

	envp = g_minish.env;
	while (envp)
	{
		i = 0;
		tmp = envp->content;
		while (key[i] && tmp[i] && (key[i] == tmp[i]))
			i++;
		if (!key[i] && (tmp[i] == '=' || tmp[i] == '\0'))
		{
			value = ft_strdup(&(tmp[i + 1]));
			if (!value)
				return (NULL);
			return (value);
		}
		envp = envp->next;
	}
	return (NULL);
}
char	*replace_env_value(char **ptr, char *var, char *value)
{
	char	*temp;
	char	*final;

	temp = ft_strjoin(var, "=");
	if (!temp)
		return (NULL);
	final = ft_strjoin(temp, value);
	if (!final)
		return (NULL);
	free(temp);
	temp = NULL;
	free(*ptr);
	*ptr = NULL;
	return (final);
}

void	replace_one_var(char **str)
{
	char	*env;
	char	*trim;

	env = ft_getenv(*str + 1);
	if (!env)
	{
		free(*str);
		*str = ft_strdup("");
		if (!*str)
			return ;
		return ;
	}
	trim = ft_strtrim(env, " ");
	if (!trim)
		return ;
	free(env);
	free(*str);
	*str = trim;
}

void	update_env_var(char *var, char *value, t_list *env)
{
	int		i;
	char	*cur_env;

	while (env)
	{
		i = 0;
		cur_env = (env->content);
		while (var[i] && cur_env[i] && (var[i] == cur_env[i]))
			i++;
		if (!var[i] && (cur_env[i] == '=' || cur_env[i] == '\0' ))
			env->content = replace_env_value(&cur_env, var, value);
		env = env->next;
	}
}
