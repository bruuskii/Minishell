/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:12:26 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:12:27 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
