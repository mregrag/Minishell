/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:03:11 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/01 14:46:13 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
// Swap function
static void ft_swap(void **a, void **b)
{
    void *temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for quicksort
static int ft_partition(void **arr, int low, int high, int (*cmp)(const void *, const void *))
{
    void *pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (cmp(arr[j], pivot) < 0)
        {
            i++;
            ft_swap(&arr[i], &arr[j]);
        }
    }
    ft_swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Recursive quicksort function
static void ft_qsort_recursive(void **arr, int low, int high, int (*cmp)(const void *, const void *))
{
    if (low < high)
    {
        int pi = ft_partition(arr, low, high, cmp);

        ft_qsort_recursive(arr, low, pi - 1, cmp);
        ft_qsort_recursive(arr, pi + 1, high, cmp);
    }
}

// Main quicksort function
void ft_qsort(void **arr, int size, int (*cmp)(const void *, const void *))
{
    ft_qsort_recursive(arr, 0, size - 1, cmp);
}

// Comparison function for sorting strings
static int compare_strings(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}
int values[] = { 'b', 'c', 'a', 'e', 't' };
int main () {
   int n;

   printf("Before sorting the list is: \n");
   for( n = 0 ; n < 5; n++ ) {
      printf("%d ", values[n]);
   }

   qsort(values, 5, sizeof(int), compare_strings);

   printf("\nAfter sorting the list is: \n");
   for( n = 0 ; n < 5; n++ ) {
      printf("%d ", values[n]);
   }

   return(0);
}
