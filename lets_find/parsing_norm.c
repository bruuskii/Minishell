/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:03:07 by izouine           #+#    #+#             */
/*   Updated: 2024/09/02 14:11:14 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	processs_token(t_token *current, t_env *env, char **tokens, int index)
{
	int	args_nbr;
	int	is_command;

	args_nbr = 0;
	is_command = 1;
	grep_type(current, index, is_command);
	expand(current, env, tokens, index);
	handle_quotes_and_args(current, &args_nbr, index);
	update_command_status(current, &is_command, &args_nbr);
}

t_token	*tokenize_input(char **tokens, t_env *env)
{
	return (tokenize_input_helper(tokens, env));
}

void	grep_type(t_token *token, int index, int is_command)
{
	if (ft_strcmp(token->token, " ") == 0)
	{
		if (token->prev && (ft_strcmp(token->prev->type, "command") == 0
				|| ft_strcmp(token->prev->type, "pipe") == 0))
			token->type = "space";
		else
			grep_type_space(token);
	}
	else if (is_redirect_out(token))
		token->type = "out";
	else if (is_redirect_in(token))
		token->type = "in";
	else if (iss_operator(token->token))
		token->type = "operator";
	else if (ft_strcmp(token->token, "|") == 0)
		token->type = "pipe";
	else if (is_command_token(token, index, is_command))
		token->type = "command";
	else
		token->type = "argument";
}
