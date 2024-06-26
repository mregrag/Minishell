/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:03:11 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/26 14:17:00 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main()
{
	// close(STDOUT_FILENO);
	close(STDIN_FILENO);
	if (isatty(STDOUT_FILENO))
		printf("Standard output is connected to a terminal.\n");
	else
		printf("Standard output is not connected to a terminal.\n");

	if (isatty(STDIN_FILENO))
		printf("Standard input is connected to a terminal.\n");
	else
		printf("Standard input is not connected to a terminal.\n");

	return 0;
}
