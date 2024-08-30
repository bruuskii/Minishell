/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:41:42 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:10:58 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Libft/libft.h"
#include "minishell.h"

char	*process_char(char *final, t_token *token, t_env *env,
		t_process_info *info)
{
	if (token->token[info->i] == '\'' && !info->in_d_quote)
		final = handle_quotes(final, token->token[info->i], &info->in_s_quote);
	else if (token->token[info->i] == '"' && !info->in_s_quote)
		final = handle_quotes(final, token->token[info->i], &info->in_d_quote);
	else if (!info->in_s_quote && token->token[info->i] == '$')
		final = handle_dollar_sign(final, token, env, &info->i);
	else
		final = append_char(final, token->token[info->i]);
	return (final);
}

char	*process_token_loop(t_token *token, t_env *env, char *final)
{
	t_process_info	info;

	info.i = 0;
	info.in_s_quote = 0;
	info.in_d_quote = 0;
	info.token_len = ft_strlen(token->token);
	while (info.i < info.token_len)
	{
		final = process_char(final, token, env, &info);
		if (!final)
			return (NULL);
		info.i++;
	}
	return (final);
}

char	*process_tokennn(t_token *token, t_env *env)
{
	char	*final;
	size_t	token_len;

	final = ft_strdup("");
	if (!final)
		return (NULL);
	token_len = ft_strlen(token->token);
	if (token_len >= 3 && token->token[0] == '$' && (token->token[1] == '\''
			|| token->token[1] == '"') && ft_strcmp(token->type,
			"command") == 0)
		return (handle_special_command(token));
	return (process_token_loop(token, env, final));
}
