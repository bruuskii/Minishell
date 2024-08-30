/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:59:42 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:16:19 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	link_tokens(t_token **head, t_token **current, t_token *new_token)
{
	if (*current)
		(*current)->next = new_token;
	else
		*head = new_token;
	new_token->prev = *current;
	*current = new_token;
}

int	initialize_print_type(char *str, char ***tokens)
{
	if (!str || !first_parse(str))
		return (0);
	*tokens = split_string(str);
	if (!*tokens || !parse_every_word(*tokens))
	{
		free_string_array(*tokens);
		return (0);
	}
	return (1);
}

int	finalize_print_type(t_token *head, t_cmd **cmd)
{
	*cmd = parse_every_command(head);
	if (!(*cmd))
	{
		free(cmd);
		return (0);
	}
	free_tokens(head);
	return (1);
}

void	grep_type_space(t_token *token)
{
	t_token	*mine;

	if (ft_strcmp(token->prev->type, "command") == 0)
	{
		token->type = "argument";
		return ;
	}
	mine = token;
	while (mine->prev && ft_strcmp(mine->prev->token, "|") != 0)
		mine = mine->prev;
	if (ft_strcmp(mine->token, "|") == 0)
		mine = mine->next;
	if (ft_strcmp(mine->token, "echo") == 0 && ft_strncmp(mine->next->token,
			"-", 1) != 0)
		token->type = "argument";
	else
		token->type = "space";
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}
