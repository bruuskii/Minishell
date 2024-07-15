/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:28:03 by ainouni           #+#    #+#             */
/*   Updated: 2023/11/23 16:46:08 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_blanks(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_atoi(const char *nptr)
{
	unsigned long long	result;
	int					i;
	int					sign;

	i = 0;
	result = 0;
	sign = 1;
	while (is_blanks(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - 48);
		if (result > 9223372036854775807 && sign == 1)
			return (-1);
		else if (result > 9223372036854775807 && sign == -1)
			return (0);
		i++;
	}
	return (result * sign);
}
