/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:07:23 by izouine           #+#    #+#             */
/*   Updated: 2024/08/18 15:08:42 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_start_end(char *line, int len)
{
	int	i;

	i = 0;
	while (isspace(line[i]))
		i++;
	if (is_operator(&line[i]) && ft_strncmp(&line[i], "<", 1) != 0
		&& ft_strncmp(&line[i], "<<", 2) != 0)
		return (0);
	while (len > 0 && isspace(line[len]))
		len--;
	if (is_operator(&line[len]))
		return (0);
	return (1);
}

static int	check_operators(char *line)
{
	int	i;
	int	j;
	int	op_len;

	i = 0;
	while (line[i])
	{
		op_len = is_operator(&line[i]);
		if (op_len)
		{
			j = i + op_len;
			while (line[j] && isspace(line[j]))
				j++;
			if (!line[j] || is_operator(&line[j]))
				return (0);
		}
		i++;
	}
	return (1);
}

static int	count_quotes(char *line)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			single_quotes++;
		else if (line[i] == '"')
			double_quotes++;
		i++;
	}
	return ((single_quotes % 2 == 0) && (double_quotes % 2 == 0));
}

int	first_parse(char *line)
{
	int	len;

	if (!line)
		return (0);
	len = ft_strlen(line) - 1;
	if (!check_start_end(line, len))
		return (error_return());
	if (!check_operators(line))
		return (error_return());
	if (!count_quotes(line))
		return (error_return());
	return (1);
}

int	error_return(void)
{
	ft_putstr_fd("bash: Syntax error near \\n\n", 2);
	return (0);
}

int	check_outfiles(char *str, int index)
{
	if (str[index] == '>' && str[index + 1] == '>' && str[index + 2] == '>')
		return (1);
	return (0);
}
