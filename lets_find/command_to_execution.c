/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:15:00 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:05:50 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_every_command(t_token *token)
{
	t_cmd	*cmd_head;
	t_cmd	*cmd_current;
	t_cmd	*new_cmd;

	cmd_head = NULL;
	cmd_current = NULL;
	while (token)
	{
		new_cmd = parse_command(&token);
		if (!new_cmd)
		{
			free(new_cmd->cmd);
			free(new_cmd);
			return (NULL);
		}
		if (cmd_current)
			cmd_current->next = new_cmd;
		else
			cmd_head = new_cmd;
		cmd_current = new_cmd;
		if (token && ft_strcmp(token->type, "pipe") == 0)
			token = token->next;
	}
	return (cmd_head);
}
