/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splite_by_spaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 07:27:21 by mregrag           #+#    #+#             */
/*   Updated: 2024/08/14 07:27:55 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t ft_count_words(const char *s)
{
	size_t words = 0;
	int in_word = 0;

	while (*s)
	{
		if (ft_isspace(*s))
		{
			in_word = 0;
		}
		else if (!in_word)
		{
			in_word = 1;
			words++;
		}
		s++;
	}
	return words;
}

static void *ft_free_matrix(char **matrix, int i)
{
	while (i--)
		free(matrix[i]);
	free(matrix);
	return NULL;
}

static char **ft_split_words(char **matrix, char const *s)
{
	int i = 0;
	int start = 0;
	int in_word = 0;

	while (*s)
	{
		if (ft_isspace(*s))
		{
			if (in_word)
			{
				matrix[i] = ft_substr(s - (in_word - start), start, in_word - start);
				if (matrix[i] == NULL)
					return ft_free_matrix(matrix, i);
				i++;
				in_word = 0;
			}
		}
		else
		{
			if (!in_word)
				start = in_word;
			in_word++;
		}
		s++;
	}
	if (in_word)
	{
		matrix[i] = ft_substr(s - in_word, start, in_word);
		if (matrix[i] == NULL)
			return ft_free_matrix(matrix, i);
		i++;
	}
	matrix[i] = NULL;
	return matrix;
}

char **ft_splite_by_spaces(char const *s)
{
	char **matrix;
	if (!s)
		return NULL;
	matrix = malloc((ft_count_words(s) + 1) * sizeof(char *));
	if (!matrix)
		return NULL;
	return ft_split_words(matrix, s);
}


