/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 10:45:52 by izouine           #+#    #+#             */
/*   Updated: 2024/08/31 11:56:24 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_result(char **result)
{
	int	i;

	if (!result)
		return ;
	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}

char	**split_string_helper(const char *str, int token_count)
{
	char	**result;

	result = init_result(token_count);
	if (!result)
		return (NULL);
	if (!split_string_loop(str, result))
	{
		free_result(result);
		return (NULL);
	}
	return (result);
}

char	**split_string(const char *str)
{
	int	token_count;

	if (!str)
		return (NULL);
	token_count = count_tokens_split(str);
	if (token_count <= 0)
		return (NULL);
	return (split_string_helper(str, token_count));
}
