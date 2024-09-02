/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_username <your_email@student.42.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:00:00 by your_username    #+#    #+#             */
/*   Updated: 2023/08/18 10:00:00 by your_username   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_quote(char c, char *current_quote)
{
	if (*current_quote == '\0')
	{
		if (c == '\'' || c == '"')
			*current_quote = c;
	}
	else if (c == *current_quote)
		*current_quote = '\0';
}

int	check_quotes(char *token, char *current_quote)
{
	int	i;

	i = 0;
	while (token[i])
	{
		process_quote(token[i], current_quote);
		i++;
	}
	return (*current_quote != '\0');
}

int	parse_every_word(char **tokens)
{
	int		index;
	char	current_quote;
	int		unclosed;

	current_quote = '\0';
	index = 0;
	unclosed = 0;
	while (tokens && tokens[index] != NULL)
	{
		unclosed = check_quotes(tokens[index], &current_quote);
		index++;
	}
	if (unclosed)
	{
		ft_putstr_fd("bash: unclosed quotes\n", 2);
		return (0);
	}
	return (1);
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

char	*double_quotes(char *token)
{
	char	*new_token;
	int		i;
	int		pos;
	char	start_quote;

	if (!token)
		return (NULL);
	new_token = malloc((ft_strlen(token) + 1) * sizeof(char));
	if (!new_token)
		return (NULL);
	i = 0;
	pos = 0;
	start_quote = '\0';
	if (is_quote(token[0]))
		start_quote = token[i++];
	while (token[i])
	{
		if (token[i] == start_quote && token[i + 1] == '\0')
			break ;
		new_token[pos++] = token[i++];
	}
	new_token[pos] = '\0';
	return (new_token);
}
