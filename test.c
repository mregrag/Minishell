/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:16:08 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/20 03:24:29 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main(int agrc, char **argv, char **env)
{
	char *test[] = {"hello", NULL};
	if (execve("/bin/ls", &test[0], env) == -1) {
		perror("execve failed");
		printf("errno: %d\n", errno);
	}
	return 0;
}
