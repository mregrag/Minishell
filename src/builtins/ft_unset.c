/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:51:07 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/06 21:54:25 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_var_unset(char *var)
{
	int	i;

	i = 1;
	if (!var || *var == '\0')
		return (0);
	if (!ft_isalpha(*var) && *var != '_')
		return (0);
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(t_node *node, t_env *env)
{
	char	**args;

	args = node->cmd;
	while (*(++args))
	{
		if (!check_var_unset(*args))
		{
			print_error("minishell", "unset", *args, "not a valid identifier");
			return (exit_status(1, env), 1);
		}
		else
			unset_env_var(env, *args);
	}
	return (1);
}
