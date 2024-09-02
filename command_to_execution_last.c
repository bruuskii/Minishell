/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_execution_last.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:10:49 by izouine           #+#    #+#             */
/*   Updated: 2024/08/31 12:11:12 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_operator(t_cmd *new_cmd, t_token **token)
{
	int					is_heredoc;
	int					is_input;
	int					is_append;
	t_filedescriptiom	*new_file;

	is_heredoc = (ft_strcmp((*token)->token, "<<") == 0);
	is_input = (ft_strcmp((*token)->token, "<") == 0 || is_heredoc);
	is_append = (ft_strcmp((*token)->token, ">>") == 0);
	*token = (*token)->next;
	while (*token && ft_strcmp((*token)->type, "space") == 0)
		*token = (*token)->next;
	if (!*token || (ft_strcmp((*token)->type, "in") != 0
			&& ft_strcmp((*token)->type, "out") != 0
			&& ft_strcmp((*token)->type, "argument") != 0))
		return (0);
	new_file = create_file_desc(*token);
	if (!new_file)
		return (0);
	new_file->isherdoc = is_heredoc;
	new_file->iswithappend = is_append;
	if (is_heredoc)
		new_file->delimeter = ft_strdup((*token)->token);
	add_file_to_cmd(new_cmd, new_file, is_input);
	return (1);
}

int	process_token_cmd(t_cmd *new_cmd, t_token **token, int *i)
{
	while (*token && ft_strcmp((*token)->type, "space") == 0)
		*token = (*token)->next;
	if (!*token || ft_strcmp((*token)->type, "pipe") == 0)
		return (1);
	if (ft_strcmp((*token)->type, "command") == 0 || ft_strcmp((*token)->type,
			"argument") == 0)
	{
		if (!handle_command_argument(new_cmd, *token, i))
			return (0);
	}
	else if (ft_strcmp((*token)->type, "operator") == 0)
	{
		if (!handle_operator(new_cmd, token))
		{
			free(new_cmd->cmd);
			return (0);
		}
	}
	else
		return (0);
	*token = (*token)->next;
	return (1);
}

int	allocate_cmd_array(t_cmd *new_cmd, int nbr_of_args)
{
	new_cmd->cmd = (char **)malloc((nbr_of_args + 1) * sizeof(char *));
	if (!new_cmd->cmd)
		return (0);
	return (1);
}

int	process_cmd_tokens(t_cmd *new_cmd, t_token **token)
{
	int	i;

	i = 0;
	while (*token && ft_strcmp((*token)->type, "pipe") != 0)
	{
		if (!process_token_cmd(new_cmd, token, &i))
			return (0);
	}
	new_cmd->cmd[i] = NULL;
	return (1);
}
