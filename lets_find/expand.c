/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 21:58:11 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:10:29 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Libft/libft.h"
#include "minishell.h"

int	expand(t_token *token, t_env *env, char **str, int index)
{
	char	*final;

	(void)index;
	(void)str;
	final = process_tokennn(token, env);
	if (!final)
		return (-1);
	free(token->token);
	token->token = ft_strdup(final);
	free(final);
	return (1);
}
