/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:41:34 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:14:09 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Libft/libft.h"
#include "minishell.h"

char	*handle_dollar_quote(char *final, t_token *token, size_t *i)
{
	char	quote;

	quote = token->token[*i];
	final = append_char(final, '$');
	final = append_char(final, quote);
	(*i)++;
	while (token->token[*i] && token->token[*i] != quote)
	{
		final = append_char(final, token->token[*i]);
		(*i)++;
	}
	if (token->token[*i] == quote)
	{
		final = append_char(final, quote);
		(*i)++;
	}
	return (final);
}

char	*handle_dollar_var(char *final, t_token *token, t_env *env, size_t *i)
{
	char	dest[100];
	size_t	j;

	j = 0;
	ft_memset(dest, 0, sizeof(dest));
	while ((token->token[*i] >= 65 && token->token[*i] <= 90)
		|| (token->token[*i] >= 97 && token->token[*i] <= 122))
	{
		dest[j++] = token->token[(*i)++];
	}
	(*i)--;
	final = handle_env_variable(final, dest, env);
	return (final);
}

char	*handle_dollar_sign(char *final, t_token *token, t_env *env, size_t *i)
{
	(*i)++;
	if (token->token[*i] == '\'' || token->token[*i] == '"')
		return (handle_dollar_quote(final, token, i));
	if (token->token[*i] == '?')
	{
		final = handle_exit_status(final);
		(*i)++;
	}
	else
		final = handle_dollar_var(final, token, env, i);
	return (final);
}
