/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_username <your_email@student.42.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:00:00 by your_username    #+#    #+#             */
/*   Updated: 2023/08/18 10:00:00 by your_username   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_redirect_out(t_token *token)
{
	return ((token->prev && ft_strcmp(token->prev->token, ">") == 0)
		|| (token->prev && ft_strcmp(token->prev->token, " ") == 0
			&& token->prev->prev && ft_strcmp(token->prev->prev->token,
				">") == 0) || (token->prev && ft_strcmp(token->prev->token,
				">>") == 0) || (token->prev && ft_strcmp(token->prev->token,
				" ") == 0 && token->prev->prev
			&& ft_strcmp(token->prev->prev->token, ">>") == 0));
}

int	is_redirect_in(t_token *token)
{
	return ((token->prev && ft_strcmp(token->prev->token, "<") == 0)
		|| (token->prev && ft_strcmp(token->prev->token, " ") == 0
			&& token->prev->prev && ft_strcmp(token->prev->prev->token,
				"<") == 0) || (token->prev && ft_strcmp(token->prev->token,
				"<<") == 0) || (token->prev && ft_strcmp(token->prev->token,
				" ") == 0 && token->prev->prev
			&& ft_strcmp(token->prev->prev->token, "<<") == 0));
}

int	iss_operator(char *token)
{
	return (ft_strcmp(token, "<<") == 0 || ft_strcmp(token, "<") == 0
		|| ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0);
}

int	is_command_token(t_token *token, int index, int is_command)
{
	return (index == 0 || is_command || (token->prev
			&& ft_strcmp(token->prev->token, "|") == 0)
		|| (token->token[0] == '$' && (token->token[1] == '\''
				|| token->token[1] == '"')));
}
