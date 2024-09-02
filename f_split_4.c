/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_split_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:11:31 by izouine           #+#    #+#             */
/*   Updated: 2024/08/31 12:11:34 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quoted_substring(const char *str, int *i, char quote)
{
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i])
		(*i)++;
	return (1);
}

int	handle_dollar_quote(const char *str, int *i)
{
	char	quote;

	quote = str[*i + 1];
	*i += 2;
	return (handle_quoted_substring(str, i, quote));
}

int	advance_to_end_of_word(const char *str, int *i)
{
	while (str[*i] && !is_space_split(str[*i]) && !is_operator_split(&str[*i]))
	{
		if (str[*i] == '$' && (str[*i + 1] == '\'' || str[*i + 1] == '"'))
		{
			if (!handle_dollar_quote(str, i))
				return (0);
		}
		else if (str[*i] != '"' && str[*i] != '\'')
			(*i)++;
		else
			break ;
	}
	return (1);
}

int	handle_word(const char *str, int *i, char **result, int *index)
{
	int	start;
	int	token_len;

	start = *i;
	if (!advance_to_end_of_word(str, i))
		return (0);
	token_len = *i - start;
	result[*index] = allocate_token(str, start, token_len);
	if (!result[*index])
		return (0);
	(*index)++;
	return (1);
}

int	handle_space(char **result, int *index)
{
	result[*index] = allocate_token(" ", 0, 1);
	if (!result[*index])
		return (0);
	(*index)++;
	return (1);
}
