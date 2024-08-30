/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commad_to_execution_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:34:31 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:09:16 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = NULL;
	new_cmd->infile = NULL;
	new_cmd->outfile = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

int	count_args(t_token *token)
{
	int		nbr_of_args;
	t_token	*temp;

	nbr_of_args = 0;
	temp = token;
	while (temp && ft_strcmp(temp->type, "pipe") != 0)
	{
		if (ft_strcmp(temp->type, "command") == 0 || ft_strcmp(temp->type,
				"argument") == 0)
			nbr_of_args++;
		temp = temp->next;
	}
	return (nbr_of_args);
}

void	skip_spaces(t_token **token)
{
	while (*token && ft_strcmp((*token)->type, "space") == 0)
		*token = (*token)->next;
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		free(cmd->cmd);
		free(cmd);
	}
}
