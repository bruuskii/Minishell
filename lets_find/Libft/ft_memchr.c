/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:33:21 by ainouni           #+#    #+#             */
/*   Updated: 2023/11/23 17:04:54 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	*p_end;

	p = (unsigned char *)s;
	p_end = p + n;
	while (p < p_end)
	{
		if (((char)*p == (char)c))
			return (p);
		p++;
	}
	return (NULL);
}
