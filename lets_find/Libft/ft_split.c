/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:56:06 by ainouni           #+#    #+#             */
/*   Updated: 2023/11/23 20:33:19 by ainouni          ###   ########.fr       */
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

static size_t	countwords(char const *s, char c)
{
	size_t	i;
	size_t	s_len;
	size_t	counter;

	s_len = len_str(s);
	i = 0;
	counter = 0;
	while (i < s_len)
	{
		if (s[i] != c)
		{
			counter++;
			while (i < s_len && s[i] != c)
				i++;
		}
		else
		{
			i++;
		}
	}
	return (counter);
}

static char	**split_s(char **arr, char const *s, char c, size_t n_words)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (i < n_words)
	{
		while (*s == c)
			s++;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		arr[i] = ft_substr(s, 0, len);
		s += len;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	size_t	n_word;
	char	**arr;

	if (s)
	{
		n_word = countwords(s, c);
		arr = (char **)malloc(sizeof(char *) * (n_word + 1));
		if (!arr)
			return (NULL);
		arr = split_s(arr, s, c, n_word);
		return (arr);
	}
	return (NULL);
}
