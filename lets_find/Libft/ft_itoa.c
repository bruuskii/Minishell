/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:50:32 by ainouni           #+#    #+#             */
/*   Updated: 2023/11/23 17:14:04 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_nlen(int n)
{
	int		counter;
	long	n_pos;

	counter = 0;
	n_pos = n;
	if (n_pos == 0)
		return (1);
	if (n_pos < 0)
	{
		counter++;
		n_pos *= -1;
	}
	while (n_pos > 0)
	{
		counter++;
		n_pos = n_pos / 10;
	}
	return (counter);
}

static char	*copy_n_in_arr(char *arr, int n_len, long n_pos, int n)
{
	int	i;

	if (n_pos == 0)
	{
		arr[0] = '0';
		arr[1] = '\0';
		return (arr);
	}
	i = n_len - 1;
	while (n_pos)
	{
		arr[i] = ((n_pos % 10) + 48);
		n_pos = n_pos / 10;
		i--;
	}
	if (n < 0)
		arr[0] = '-';
	arr[n_len] = '\0';
	return (arr);
}

char	*ft_itoa(int n)
{
	char	*arr;
	int		n_len;
	long	n_pos;

	n_len = count_nlen(n);
	n_pos = n;
	arr = (char *) malloc(n_len + 1);
	if (!arr)
		return (NULL);
	if (n < 0)
		n_pos = n_pos * -1;
	return (copy_n_in_arr(arr, n_len, n_pos, n));
}
