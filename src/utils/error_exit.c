/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 18:33:04 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/22 18:51:06 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_status(int status, t_env *env)
{
	char	*exit_stat;

	exit_stat = ft_itoa(status);
	set_env_var(env, "?", exit_stat);
	free(exit_stat);
}

int exec_err(char *path, char *cmd, t_env *env)
{
    struct stat path_stat;
    char *path_env;
    int ret = 0;

    if (!cmd || !*cmd)
    {
        print_error("minishell", cmd, "command not found", NULL);
        return 127;
    }

    path_env = get_env_var(env, "PATH");
    if (!path_env && !ft_strchr(cmd, '/'))
    {
        print_error("minishell", cmd, "No such file or directory", NULL);
        return 127;
    }

    if (!*path_env && !ft_strchr(cmd, '/'))
    {
        free(path_env);  // Free path_env before returning
        print_error("minishell", cmd, "command not found", NULL);
        return 127;
    }
    else if (!ft_strchr(cmd, '/'))
    {
        free(path_env);  // Free path_env before returning
        print_error("minishell", cmd, "command not found", NULL);
        return 127;
    }

    if (access(path, F_OK) == -1)
    {
        print_error("minishell", cmd, "No such file or directory", NULL);
        ret = 127;
    }
    else if (access(path, X_OK) == -1)
    {
        print_error("minishell", cmd, "Permission denied", NULL);
        ret = 126;
    }
    else if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
    {
        print_error("minishell", cmd, "is a directory", NULL);
        ret = 126;
    }

    free(path_env);  // Free path_env before returning
    return ret;
}
void	malloc_error(void)
{
	print_error("minish", "malloc", strerror(errno), NULL);
	exit(EXIT_FAILURE);
}

int	print_error(char *s1, char *s2, char *s3, char *message)
{
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
	{
		if (s1)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s2, 2);
	}
	if (s3)
	{
		if (s1 || s2)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s3, 2);
	}
	if (message)
	{
		if (s1 || s2 || s3)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(message, 2);
	}
	ft_putchar_fd('\n', 2);
	return (1);
}
