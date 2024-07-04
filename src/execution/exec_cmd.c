/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:58:39 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/03 23:46:15 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *get_path(char *command, t_env *env)
{
    char *path_var;
    char **paths;
    char *full_path;
    int i;

    if (!command || !env)
        return (NULL);
    if (ft_strchr(command, '/'))
        return (ft_strdup(command));
    path_var = get_env_var(env, "PATH");
    if (!path_var)
        return (NULL);

    paths = ft_split(path_var, ':');
    free(path_var); // Free path_var after splitting

    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        full_path = ft_strjoin_three(paths[i], "/", command);
        if (!full_path)
        {
            ft_free_array(paths);
            return (NULL);
        }

        if (access(full_path, X_OK) == 0)
        {
            ft_free_array(paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }

    ft_free_array(paths);
    return (NULL);
}

static void child_exec(t_node *node, t_env *env)
{
    char    **envp;
    pid_t   pid;
    int     status;
    char    *path;
    char    *exit_status;

    envp = ft_list_to_arr(env->env);
    if (!envp)
        return;

    pid = ft_fork();
    if (pid < 0)
    {
        ft_free_array(envp);
        return;
    }
    if (pid == 0)
    {
        path = get_path(node->cmd[0], env);
        if (!path)
        {
            exec_err(errno, NULL, node->cmd[0]);
            ft_free_array(envp);
            exit(127); // Exit with "command not found" status
        }
        execve(path, node->cmd, envp);
        // If execve returns, it means it failed
        exec_err(errno, path, node->cmd[0]);
        free(path); // Free path if execve fails
        ft_free_array(envp);
        exit(126); // Exit with "command invoked cannot execute" status
    }
    else
    {
        waitpid(pid, &status, 0);
        exit_status = ft_itoa(WEXITSTATUS(status));
        if (exit_status)
        {
            set_env_var(env, "?", exit_status);
            free(exit_status);
        }
    }
    ft_free_array(envp); // Free envp after use
}

void exec_cmd(t_node *node, t_env *env)
{
    if (redirections(node, env))
    {
        while (node->left)
            node = node->left;
    }
    if (node->cmd && node->cmd[0] && !is_builtin(node, env))
        child_exec(node, env);
}
