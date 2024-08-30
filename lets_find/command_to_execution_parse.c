/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_execution_parse.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:34:39 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:13:17 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*allocate_new_cmd(int nbr_of_args)
{
	t_cmd	*new_cmd;

	new_cmd = init_new_cmd();
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = (char **)malloc((nbr_of_args + 1) * sizeof(char *));
	if (!new_cmd->cmd)
	{
		free(new_cmd);
		return (NULL);
	}
	return (new_cmd);
}

t_cmd	*parse_command_tokens(t_cmd *new_cmd, t_token **token)
{
	int	i;

	i = 0;
	while (*token && ft_strcmp((*token)->type, "pipe") != 0)
	{
		if (!process_token(new_cmd, token, &i))
		{
			free_cmd(new_cmd);
			return (NULL);
		}
	}
	new_cmd->cmd[i] = NULL;
	return (new_cmd);
}

t_cmd	*parse_command(t_token **token)
{
	int		nbr_of_args;
	t_cmd	*new_cmd;

	nbr_of_args = count_args(*token);
	new_cmd = allocate_new_cmd(nbr_of_args);
	if (!new_cmd)
		return (NULL);
	return (parse_command_tokens(new_cmd, token));
}
