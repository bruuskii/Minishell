/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 21:58:11 by izouine           #+#    #+#             */
/*   Updated: 2024/08/31 12:35:23 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Libft/libft.h"
#include "minishell.h"

char	*process_token_loop(t_token *token, t_env *env, char *final)
{
	size_t	i;
	int		quotes[2];
	size_t	token_len;

	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	token_len = ft_strlen(token->token);
	while (i < token_len)
	{
		if (!quotes[0] && token->token[i] == '$' && token->token[i + 1] != '\0')
			final = handle_dollar_sign(final, token, env, &i);
		else
			final = handle_regular_char(final, token, &i, quotes);
		if (!final)
			return (NULL);
		i++;
	}
	return (final);
}

char	*process_token_expand(t_token *token, t_env *env)
{
	char	*final;

	if (is_special_command(token))
		return (handle_special_command(token));
	final = ft_strdup("");
	if (!final)
		return (NULL);
	final = process_token_loop(token, env, final);
	return (final);
}

int	expand(t_token *token, t_env *env, char **str, int index)
{
	char	*final;

	(void)index;
	(void)str;
	final = process_token_expand(token, env);
	if (!final)
		return (-1);
	free(token->token);
	token->token = ft_strdup(final);
	free(final);
	return (1);
}
