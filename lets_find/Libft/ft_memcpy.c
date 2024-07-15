/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 22:12:12 by ainouni           #+#    #+#             */
/*   Updated: 2023/11/23 17:05:46 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	unsigned char	*psrc;
	unsigned char	*pdest;

	if (!dst && !src)
		return (NULL);
	psrc = (unsigned char *)src;
	pdest = (unsigned char *)dst;
	while (n--)
		*pdest++ = *psrc++;
	return (dst);
}
