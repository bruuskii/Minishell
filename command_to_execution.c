/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:15:00 by izouine           #+#    #+#             */
/*   Updated: 2024/08/31 11:56:24 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->cmd)
			free(cmd->cmd);
		free(cmd);
	}
}

t_cmd	*parse_command_cmd(t_token **token)
{
	t_cmd	*new_cmd;
	int		nbr_of_args;

	new_cmd = init_new_cmd();
	if (!new_cmd)
		return (NULL);
	nbr_of_args = count_args_cmd(*token);
	if (!allocate_cmd_array(new_cmd, nbr_of_args))
	{
		cleanup_cmd(new_cmd);
		return (NULL);
	}
	if (!process_cmd_tokens(new_cmd, token))
	{
		cleanup_cmd(new_cmd);
		return (NULL);
	}
	return (new_cmd);
}

t_cmd	*parse_every_command(t_token *token)
{
	t_cmd	*cmd_head;
	t_cmd	*cmd_current;
	t_cmd	*new_cmd;

	cmd_head = NULL;
	cmd_current = NULL;
	while (token)
	{
		new_cmd = parse_command_cmd(&token);
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
