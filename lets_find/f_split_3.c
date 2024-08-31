/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_split_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:08:25 by izouine           #+#    #+#             */
/*   Updated: 2024/08/31 12:08:54 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens_helper(const char *str, int len)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < len)
	{
		while (i < len && is_space_split(str[i]))
			i++;
		if (i >= len)
			break ;
		if (str[i] == '"' || str[i] == '\'')
			count += count_quote_token(str, &i, len);
		else if (count_operator_token(str, &i))
			count++;
		else
			count += count_word_token(str, &i, len);
		if (i < len && is_space_split(str[i]))
			count++;
		while (i < len && is_space_split(str[i]))
			i++;
	}
	return (count);
}

int	count_tokens_split(const char *str)
{
	if (!str)
		return (0);
	return (count_tokens_helper(str, ft_strlen(str)));
}

char	*allocate_token(const char *str, int start, int len)
{
	char	*token;

	token = (char *)malloc((len + 1) * sizeof(char));
	if (!token)
		return (NULL);
	ft_strlcpy(token, &str[start], len + 1);
	return (token);
}

int	handle_quote_split(const char *str, int *i, char **result, int *index)
{
	int		start;
	char	quote;
	int		token_len;

	if (*i > 0 && str[*i - 1] == '$')
		start = *i - 1;
	else
		start = *i;
	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i])
		(*i)++;
	token_len = *i - start;
	result[*index] = allocate_token(str, start, token_len);
	if (!result[*index])
		return (0);
	(*index)++;
	return (1);
}

int	handle_operator_split(const char *str, int *i, char **result, int *index)
{
	int	op_len;

	op_len = is_operator_split(&str[*i]);
	if (op_len > 0)
	{
		result[*index] = allocate_token(str, *i, op_len);
		if (!result[*index])
			return (0);
		*i += op_len;
		(*index)++;
	}
	return (1);
}
