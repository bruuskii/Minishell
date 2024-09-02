/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_split_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:06:06 by izouine           #+#    #+#             */
/*   Updated: 2024/08/31 12:39:25 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_spaces(const char *str, int *i)
{
	if (!str || !i)
		return ;
	while (str[*i] && is_space_split(str[*i]))
		(*i)++;
}

int	process_token_split(const char *str, int *i, char **result, int *index)
{
	if (str[*i] == '"' || str[*i] == '\'')
		return (handle_quote_split(str, i, result, index));
	else if (is_operator_split(&str[*i]))
		return (handle_operator_split(str, i, result, index));
	else
		return (handle_word(str, i, result, index));
}

int	process_space(const char *str, int *i, char **result, int *index)
{
	if (str[*i] && is_space_split(str[*i]))
	{
		if (!handle_space(result, index))
			return (0);
		(*i)++;
	}
	return (1);
}

char	**init_result(int token_count)
{
	char	**result;

	result = (char **)malloc((token_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (result);
}

int	split_string_loop(const char *str, char **result)
{
	int	i;
	int	index;
	int	skip_space;

	i = 0;
	index = 0;
	skip_space = 1;
	if (!str || !result)
		return (0);
	while (str[i])
	{
		if (skip_space && str[i])
			skip_spaces(str, &i);
		if (!str[i])
			break ;
		if (!process_token_split(str, &i, result, &index))
			return (0);
		if (!skip_space && !process_space(str, &i, result, &index))
			return (0);
		skip_space = 0;
		skip_spaces(str, &i);
	}
	result[index] = NULL;
	return (1);
}
