/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:03:11 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/29 17:06:10 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	ft_free(void *ptr)
{
	void	**p;

	p = (void **)ptr;
	if (p != NULL && *p != NULL)
	{
		free(*p);
		*p = NULL;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (strdup(s2));
	if (!s2)
		return (strdup(s1));
	result = malloc(sizeof(char) *(strlen(s1) + strlen(s2) + 1));
	if (!result)
		return (NULL);
	while (*s1)
		*(result + i++) = *s1++;
	while (*s2)
		*(result + i++) = *s2++;
	*(result + i) = '\0';
	return (result);
}

void	leak(void)
{
	system("leaks a.out");
}
int main()
{
	atexit(leak);
	char *s;
	s =  ft_strjoin("hello", NULL);
	printf("s = %s\n", s);
	ft_free(&s);

	return 0;
}
