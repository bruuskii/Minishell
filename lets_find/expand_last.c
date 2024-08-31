/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_last.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:39:34 by izouine           #+#    #+#             */
/*   Updated: 2024/08/31 11:58:35 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Libft/libft.h"
#include "minishell.h"

char	*handle_env_var(char *final, t_token *token, t_env *env, size_t *i)
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
	return (handle_env_variable(final, dest, env));
}

char	*handle_dollar_sign(char *final, t_token *token, t_env *env, size_t *i)
{
	(*i)++;
	if (token->token[*i] == '\'' || token->token[*i] == '"')
		return (handle_quoted_dollar(final, token, i));
	if (token->token[*i] == '?')
	{
		final = handle_exit_status(final);
		(*i)++;
	}
	else
		final = handle_env_var(final, token, env, i);
	return (final);
}

char	*handle_special_command(t_token *token)
{
	char	*final;
	size_t	i;
	size_t	token_len;

	final = ft_strdup("");
	if (!final)
		return (NULL);
	token_len = ft_strlen(token->token);
	i = 2;
	while (i < token_len - 1)
	{
		final = append_char(final, token->token[i]);
		i++;
	}
	return (final);
}

int	is_special_command(t_token *token)
{
	size_t	token_len;

	token_len = ft_strlen(token->token);
	return (token_len >= 3 && token->token[0] == '$' && (token->token[1] == '\''
			|| token->token[1] == '"') && ft_strcmp(token->type,
			"command") == 0);
}

char	*handle_regular_char(char *final, t_token *token, size_t *i,
		int *quotes)
{
	if (token->token[*i] == '\'' && !quotes[1])
	{
		quotes[0] = !quotes[0];
		final = append_char(final, token->token[*i]);
	}
	else if (token->token[*i] == '"' && !quotes[0])
	{
		quotes[1] = !quotes[1];
		final = append_char(final, token->token[*i]);
	}
	else
		final = append_char(final, token->token[*i]);
	return (final);
}
