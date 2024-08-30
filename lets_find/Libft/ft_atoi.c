/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:28:03 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/30 18:22:12 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

unsigned long long	ft_atoi(const char *nptr)
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
			return (2);
		else if (result > 9223372036854775807 && sign == -1)
			return (0);
		i++;
	}
	return (result * sign);
}
