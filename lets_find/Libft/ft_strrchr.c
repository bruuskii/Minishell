/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:07:57 by ainouni           #+#    #+#             */
/*   Updated: 2023/11/23 20:36:57 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_str(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (*s && s[i])
		i++;
	return (i);
}

char	*ft_strrchr(const char *s, int c)
{
	size_t	s_len;

	s_len = len_str(s);
	if (!s)
		return (NULL);
	if (s[s_len] == (char)c)
		return ((char *)&s[s_len]);
	while (s_len > 0)
	{
		s_len--;
		if (s[s_len] == (char)c)
			return ((char *)&s[s_len]);
	}
	return (NULL);
}
