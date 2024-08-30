/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:02:47 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/26 16:57:02 by ainouni          ###   ########.fr       */
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

static char	*ft_strcpy(char *str, char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*str;
	size_t	len;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	len = len_str(s1) + len_str(s2);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	ft_strcpy(str, (char *)s1);
	ft_strcpy((str + len_str(s1)), (char *)s2);
	free(s1);
	if (!str)
		return (NULL);
	return (str);
}
