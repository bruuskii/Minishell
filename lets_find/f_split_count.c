/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_split_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:24:24 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:14:41 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_quote_token(const char *str, int *i, int len)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (*i < len && str[*i] != quote)
		(*i)++;
	if (*i < len)
		(*i)++;
	return (1);
}

static int	count_operator_token(const char *str, int *i)
{
	int	op_len;

	op_len = is_operator(&str[*i]);
	if (op_len > 0)
	{
		*i += op_len;
		return (1);
	}
	return (0);
}

static int	count_word_token(const char *str, int *i, int len)
{
	while (*i < len && !is_space(str[*i]) && !is_operator(&str[*i])
		&& str[*i] != '"' && str[*i] != '\'')
		(*i)++;
	return (1);
}

static int	count_tokens_helper(const char *str, int len)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < len)
	{
		while (i < len && is_space(str[i]))
			i++;
		if (i >= len)
			break ;
		if (str[i] == '"' || str[i] == '\'')
			count += count_quote_token(str, &i, len);
		else if (count_operator_token(str, &i))
			count++;
		else
			count += count_word_token(str, &i, len);
		if (i < len && is_space(str[i]))
			count++;
		while (i < len && is_space(str[i]))
			i++;
	}
	return (count);
}

int	count_tokens(const char *str)
{
	if (!str)
		return (0);
	return (count_tokens_helper(str, ft_strlen(str)));
}
