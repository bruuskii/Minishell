/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_split_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:24:18 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:11:40 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_tokenn(t_token_info *info)
{
	if (info->str[*info->i] == '"' || info->str[*info->i] == '\'')
		return (handle_quote(info));
	else if (is_operator(&info->str[*info->i]))
		return (handle_operator(info));
	else
		return (handle_word(info));
}

int	process_space(t_token_info *info)
{
	if (info->str[*info->i] && is_space(info->str[*info->i]))
	{
		if (!handle_space(info))
			return (0);
		(*info->i)++;
	}
	return (1);
}

int	handle_space(t_token_info *info)
{
	info->result[*info->index] = allocate_token(" ", 0, 1);
	if (!info->result[*info->index])
		return (0);
	(*info->index)++;
	return (1);
}
