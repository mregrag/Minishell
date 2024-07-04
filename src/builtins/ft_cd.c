/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:49:44 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/03 19:22:07 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *get_dir(t_node *node, t_env *env) {
    char *pwd = NULL;

    if (!node->cmd[1]) {
        pwd = get_env_var(env, "HOME");
        if (!pwd)
            print_error("minish", "cd", "HOME not set", NULL);
    } else if (node->cmd[1] && ft_strncmp(node->cmd[1], "-", 2) == 0) {
        pwd = get_env_var(env, "OLDPWD");
        if (!pwd)
            print_error("minish", "cd", "OLDPWD not set", NULL);
    } else {
        pwd = ft_strdup(node->cmd[1]);
    }
    return pwd;
}

static int update_pwd(t_env *env) {
    char buf[PATH_MAX];
    char *old_pwd = get_env_var(env, "PWD");

    if (old_pwd) {
        set_env_var(env, "OLDPWD", old_pwd);
        free(old_pwd);
    }

    if (!getcwd(buf, sizeof(buf))) {
        print_error_errno("cd", "error retrieving current directory", "getcwd :  cannot access parent directories");
        return 1;
    }
    set_env_var(env, "PWD", buf);
    return 0;
}

int ft_cd(t_node *node, t_env *env) {
    char *pwd = get_dir(node, env);

    if (!pwd)
        return 1;

    if (chdir(pwd) == -1) {
        print_error_errno("minish", "cd", pwd);
        free(pwd);
        return 1;
    }

    if (node->cmd[1] && !ft_strcmp(node->cmd[1], "-"))
        printf("%s\n", pwd);
    if (update_pwd(env) == 1) {
        free(pwd);
        return 1;
    }
    free(pwd);
    return 0;
}
