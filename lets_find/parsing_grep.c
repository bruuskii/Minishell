/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_grep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:01:35 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:12:16 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	grep_type_helper(t_token *token, int index, int is_command)
{
	if (is_output_redirection(token))
		token->type = "out";
	else if (is_input_redirection(token))
		token->type = "in";
	else if (is_token_operator(token))
		token->type = "operator";
	else if (is_token_command(token, index, is_command))
		token->type = "command";
	else if (ft_strcmp(token->token, "|") == 0)
		token->type = "pipe";
	else
		token->type = "argument";
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
	else
		grep_type_helper(token, index, is_command);
	printf("token , %s .. type %s\n", token->token, token->type);
}

char	*double_quotes(char *token)
{
	t_token_process	tp;
	char			start_quote;

	if (!token)
		return (NULL);
	tp.new_token = malloc((ft_strlen(token) + 1) * sizeof(char));
	if (!tp.new_token)
		return (NULL);
	tp.token = token;
	tp.i = 0;
	tp.pos = 0;
	start_quote = '\0';
	if (is_quote(token[0]))
		start_quote = token[tp.i++];
	while (token[tp.i])
	{
		if (token[tp.i] == start_quote && token[tp.i + 1] == '\0')
			break ;
		tp.new_token[tp.pos++] = token[tp.i++];
	}
	tp.new_token[tp.pos] = '\0';
	return (tp.new_token);
}
