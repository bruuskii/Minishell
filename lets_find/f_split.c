/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 22:29:13 by izouine           #+#    #+#             */
/*   Updated: 2024/08/16 22:29:52 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	is_operator(const char *str)
{
	const char	*operations[] = {"<<", "<", ">>", ">", "|", "\"\"", "\'\'"};
	int			num_operations;
	int			op_len;
	int			k;

	num_operations = sizeof(operations) / sizeof(operations[0]);
	k = 0;
	while (k < num_operations)
	{
		op_len = ft_strlen(operations[k]);
		if (ft_strncmp(str, operations[k], op_len) == 0)
			return (op_len);
		k++;
	}
	return (0);
}

static int	count_quote_token(const char *str, int *i, int len)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (*i < len && str[*i] != quote)
		(*i)++;
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

static int	count_tokens(const char *str)
{
	return (count_tokens_helper(str, ft_strlen(str)));
}

static char	*allocate_token(const char *str, int start, int len)
{
	char	*token;

	token = (char *)malloc((len + 1) * sizeof(char));
	if (!token)
		return (NULL);
	ft_strlcpy(token, &str[start], len + 1);
	return (token);
}

static int	handle_quote(const char *str, int *i, char **result, int *index)
{
	char	quote;
	int		start;
	int		token_len;

	quote = str[*i];
	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	(*i)++;
	token_len = *i - start;
	result[*index] = allocate_token(str, start, token_len);
	if (!result[*index])
		return (0);
	(*index)++;
	return (1);
}

static int	handle_operator(const char *str, int *i, char **result, int *index)
{
	int	op_len;

	op_len = is_operator(&str[*i]);
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

static int	handle_word(const char *str, int *i, char **result, int *index)
{
	int	start;
	int	token_len;

	start = *i;
	while (str[*i] && !is_space(str[*i]) && !is_operator(&str[*i])
		&& str[*i] != '"' && str[*i] != '\'')
		(*i)++;
	token_len = *i - start;
	result[*index] = allocate_token(str, start, token_len);
	if (!result[*index])
		return (0);
	(*index)++;
	return (1);
}

static int	handle_space(char **result, int *index)
{
	result[*index] = allocate_token(" ", 0, 1);
	if (!result[*index])
		return (0);
	(*index)++;
	return (1);
}

static int	process_token(const char *str, int *i, char **result, int *index)
{
	if (str[*i] == '"' || str[*i] == '\'')
		return (handle_quote(str, i, result, index));
	else if (is_operator(&str[*i]))
		return (handle_operator(str, i, result, index));
	else
		return (handle_word(str, i, result, index));
}

static void	skip_spaces(const char *str, int *i)
{
	while (str[*i] && is_space(str[*i]))
		(*i)++;
}

static int	process_space(const char *str, int *i, char **result,
		int *index)
{
	if (str[*i] && is_space(str[*i]))
	{
		if (!handle_space(result, index))
			return (0);
		(*i)++;
	}
	return (1);
}

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
	int	i;
	int	index;
	int	skip_space;

	i = 0;
	index = 0;
	skip_space = 1;
	while (str[i])
	{
		if (skip_space)
			skip_spaces(str, &i);
		if (!str[i])
			break ;
		if (!process_token(str, &i, result, &index))
			return (0);
		if (!skip_space && !process_space(str, &i, result, &index))
			return (0);
		skip_space = 0;
		skip_spaces(str, &i);
	}
	result[index] = NULL;
	return (1);
}

static void	free_result(char **result)
{
	int	i;

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
	int		token_count;
	char	**result;

	token_count = count_tokens(str);
	result = split_string_helper(str, token_count);
	return (result);
}
