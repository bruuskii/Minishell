/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_split_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:07:58 by izouine           #+#    #+#             */
/*   Updated: 2024/08/31 12:08:03 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space_split(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	is_operator_split(const char *str)
{
	const char	*operations[] = {"<<", "<", ">>", ">", "|"};
	int			num_operations;
	int			op_len;
	int			k;

	k = 0;
	num_operations = sizeof(operations) / sizeof(operations[0]);
	while (k < num_operations)
	{
		op_len = ft_strlen(operations[k]);
		if (ft_strncmp(str, operations[k], op_len) == 0)
		{
			if (!(str[0] == '$' && (str[1] == '\'' || str[1] == '"')))
				return (op_len);
		}
		k++;
	}
	return (0);
}

int	count_quote_token(const char *str, int *i, int len)
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

int	count_operator_token(const char *str, int *i)
{
	int	op_len;

	op_len = is_operator_split(&str[*i]);
	if (op_len > 0)
	{
		*i += op_len;
		return (1);
	}
	return (0);
}

int	count_word_token(const char *str, int *i, int len)
{
	while (*i < len && !is_space_split(str[*i]) && !is_operator_split(&str[*i])
		&& str[*i] != '"' && str[*i] != '\'')
		(*i)++;
	return (1);
}
