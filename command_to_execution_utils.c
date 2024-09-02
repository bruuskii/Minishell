/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_execution_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:04:00 by izouine           #+#    #+#             */
/*   Updated: 2024/08/31 12:04:14 by izouine          ###   ########.fr       */
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

int	count_args_cmd(t_token *token)
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

t_filedescriptiom	*create_file_desc(t_token *token)
{
	t_filedescriptiom	*new_file;

	new_file = (t_filedescriptiom *)malloc(sizeof(t_filedescriptiom));
	if (!new_file)
		return (NULL);
	new_file->filename = ft_strdup(token->token);
	new_file->isherdoc = 0;
	new_file->iswithappend = 0;
	new_file->next = NULL;
	new_file->delimeter = NULL;
	return (new_file);
}

void	add_file_to_cmd(t_cmd *cmd, t_filedescriptiom *new_file, int is_infile)
{
	t_filedescriptiom	**last_file;

	if (is_infile)
		last_file = &(cmd->infile);
	else
		last_file = &(cmd->outfile);
	while (*last_file)
		last_file = &((*last_file)->next);
	*last_file = new_file;
}

int	handle_command_argument(t_cmd *new_cmd, t_token *token, int *i)
{
	new_cmd->cmd[(*i)++] = ft_strdup(token->token);
	return (1);
}
