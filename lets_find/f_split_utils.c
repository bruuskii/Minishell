/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_split_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:24:15 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:15:01 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

static int	is_operator_helper(const char *str, const char *op, int op_len)
{
	if (ft_strncmp(str, op, op_len) == 0)
	{
		if (!(str[0] == '$' && (str[1] == '\'' || str[1] == '"')))
			return (op_len);
	}
	return (0);
}

int	is_operator(const char *str)
{
	const char	*operations[] = {"<<", "<", ">>", ">", "|"};
	int			num_operations;
	int			op_len;
	int			k;

	num_operations = sizeof(operations) / sizeof(operations[0]);
	k = 0;
	while (k < num_operations)
	{
		op_len = ft_strlen(operations[k]);
		if (is_operator_helper(str, operations[k], op_len))
			return (op_len);
		k++;
	}
	return (0);
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

void	skip_spacess(const char *str, int *i)
{
	if (!str || !i)
		return ;
	while (str[*i] && is_space(str[*i]))
		(*i)++;
}
