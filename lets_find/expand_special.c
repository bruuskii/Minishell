/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:41:19 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:14:24 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Libft/libft.h"
#include "minishell.h"

char	*handle_special_command(t_token *token)
{
	char	*final;
	size_t	i;
	size_t	token_len;

	final = ft_strdup("");
	if (!final)
		return (NULL);
	i = 2;
	token_len = ft_strlen(token->token);
	while (i < token_len - 1)
	{
		final = append_char(final, token->token[i]);
		i++;
	}
	return (final);
}

char	*handle_quotes(char *final, char c, int *in_quote)
{
	*in_quote = !(*in_quote);
	return (append_char(final, c));
}
