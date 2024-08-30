/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_split_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:24:20 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:07:59 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_quote_start(t_token_info *info)
{
	if (*info->i > 0 && info->str[*info->i - 1] == '$')
		return (*info->i - 1);
	return (*info->i);
}

int	handle_quote(t_token_info *info)
{
	int		start;
	char	quote;
	int		token_len;

	start = get_quote_start(info);
	quote = info->str[*info->i];
	(*info->i)++;
	while (info->str[*info->i] && info->str[*info->i] != quote)
		(*info->i)++;
	if (info->str[*info->i])
		(*info->i)++;
	token_len = *info->i - start;
	info->result[*info->index] = allocate_token(info->str, start, token_len);
	if (!info->result[*info->index])
		return (0);
	(*info->index)++;
	return (1);
}

int	handle_operator(t_token_info *info)
{
	int	op_len;

	op_len = is_operator(&info->str[*info->i]);
	if (op_len > 0)
	{
		info->result[*info->index] = allocate_token(info->str, *info->i,
				op_len);
		if (!info->result[*info->index])
			return (0);
		*info->i += op_len;
		(*info->index)++;
	}
	return (1);
}

static int	handle_word_helper(t_token_info *info, char quote)
{
	*info->i += 2;
	while (info->str[*info->i] && info->str[*info->i] != quote)
		(*info->i)++;
	if (info->str[*info->i])
		(*info->i)++;
	return (1);
}

int	handle_word(t_token_info *info)
{
	int	start;
	int	token_len;

	start = *info->i;
	while (info->str[*info->i] && !is_space(info->str[*info->i])
		&& !is_operator(&info->str[*info->i]))
	{
		if (info->str[*info->i] == '$' && (info->str[*info->i + 1] == '\''
				|| info->str[*info->i + 1] == '"'))
			handle_word_helper(info, info->str[*info->i + 1]);
		else if (info->str[*info->i] != '"' && info->str[*info->i] != '\'')
			(*info->i)++;
		else
			break ;
	}
	token_len = *info->i - start;
	info->result[*info->index] = allocate_token(info->str, start, token_len);
	if (!info->result[*info->index])
		return (0);
	(*info->index)++;
	return (1);
}
