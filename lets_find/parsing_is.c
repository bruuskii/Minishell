/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_is.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:18:21 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:09:02 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_output_redirection(t_token *token)
{
	return ((token->prev && ft_strcmp(token->prev->token, ">") == 0)
		|| (token->prev && ft_strcmp(token->prev->token, " ") == 0
			&& token->prev->prev && ft_strcmp(token->prev->prev->token,
				">") == 0) || (token->prev && ft_strcmp(token->prev->token,
				">>") == 0) || (token->prev && ft_strcmp(token->prev->token,
				" ") == 0 && token->prev->prev
			&& ft_strcmp(token->prev->prev->token, ">>") == 0));
}

int	is_input_redirection(t_token *token)
{
	return ((token->prev && ft_strcmp(token->prev->token, "<") == 0)
		|| (token->prev && ft_strcmp(token->prev->token, " ") == 0
			&& token->prev->prev && ft_strcmp(token->prev->prev->token,
				"<") == 0) || (token->prev && ft_strcmp(token->prev->token,
				"<<") == 0) || (token->prev && ft_strcmp(token->prev->token,
				" ") == 0 && token->prev->prev
			&& ft_strcmp(token->prev->prev->token, "<<") == 0));
}

int	is_token_operator(t_token *token)
{
	return (is_operator(token->token));
}

int	is_token_command(t_token *token, int index, int is_command)
{
	return (index == 0 || is_command || (token->prev
			&& ft_strcmp(token->prev->token, "|") == 0)
		|| (token->token[0] == '$' && (token->token[1] == '\''
				|| token->token[1] == '"')));
}
