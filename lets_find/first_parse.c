/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:07:23 by izouine           #+#    #+#             */
/*   Updated: 2024/08/31 12:36:19 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_start_end(char *line, int len)
{
	int	i;

	i = 0;
	while (isspace(line[i]))
		i++;
	if (is_operator_split(&line[i]) && ft_strncmp(&line[i], "<", 1) != 0
		&& ft_strncmp(&line[i], "<<", 2) != 0)
		return (0);
	while (len > 0 && isspace(line[len]))
		len--;
	if (is_operator_split(&line[len]))
		return (0);
	return (1);
}

int	check_operators(char *line)
{
	int	i;
	int	j;
	int	op_len;

	i = 0;
	while (line[i])
	{
		op_len = is_operator_split(&line[i]);
		if (op_len)
		{
			j = i + op_len;
			while (line[j] && isspace(line[j]))
				j++;
			if (!line[j] || is_operator_split(&line[j]))
				return (0);
		}
		i++;
	}
	return (1);
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
	return (1);
}

int	error_return(void)
{
	ft_putstr_fd("bash: Syntax error near \\n\n", 2);
	g_exec->exit_status = 2;
	return (0);
}

int	check_outfiles(char *str, int index)
{
	if (str[index] == '>' && str[index + 1] == '>' && str[index + 2] == '>')
		return (1);
	return (0);
}
