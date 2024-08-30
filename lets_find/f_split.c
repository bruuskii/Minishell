/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_username <your_email@student.42.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by your_username    #+#    #+#             */
/*   Updated: 2023/01/01 00:00:00 by your_username   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**init_result(int token_count)
{
	char	**result;

	result = (char **)malloc((token_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (result);
}

static int	split_string_loop(const char *str, char **result)
{
	int				i;
	int				index;
	int				skip_space;
	t_token_info	info;

	i = 0;
	index = 0;
	skip_space = 1;
	if (!str || !result)
		return (0);
	info = (t_token_info){str, &i, result, &index};
	while (str[i])
	{
		if (skip_space && str[i])
			skip_spacess(str, &i);
		if (!str[i])
			break ;
		if (!process_tokenn(&info) || (!skip_space && !process_space(&info)))
			return (0);
		skip_space = 0;
		skip_spacess(str, &i);
	}
	result[index] = NULL;
	return (1);
}

static void	free_result(char **result)
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

static char	**split_string_helper(const char *str, int token_count)
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
	token_count = count_tokens(str);
	if (token_count <= 0)
		return (NULL);
	return (split_string_helper(str, token_count));
}
