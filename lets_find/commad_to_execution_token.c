/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commad_to_execution_token.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:34:29 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:16:08 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_filedescriptiom	*process_operator(t_token **token, int is_heredoc,
		int is_append)
{
	t_filedescriptiom	*new_file;

	*token = (*token)->next;
	while (*token && ft_strcmp((*token)->type, "space") == 0)
		*token = (*token)->next;
	if (*token && (ft_strcmp((*token)->type, "in") == 0
			|| ft_strcmp((*token)->type, "out") == 0
			|| ft_strcmp((*token)->type, "argument") == 0))
	{
		new_file = create_file_desc(*token);
		if (new_file)
		{
			new_file->isherdoc = is_heredoc;
			new_file->iswithappend = is_append;
			if (is_heredoc)
				new_file->delimeter = ft_strdup((*token)->token);
			return (new_file);
		}
	}
	return (NULL);
}

int	process_command_or_argument(t_cmd *new_cmd, t_token **token, int *i)
{
	new_cmd->cmd[(*i)++] = ft_strdup((*token)->token);
	*token = (*token)->next;
	return (1);
}

int	process_operator_token(t_cmd *new_cmd, t_token **token)
{
	int					is_heredoc;
	int					is_input;
	int					is_append;
	t_filedescriptiom	*new_file;

	is_heredoc = (ft_strcmp((*token)->token, "<<") == 0);
	is_input = (ft_strcmp((*token)->token, "<") == 0 || is_heredoc);
	is_append = (ft_strcmp((*token)->token, ">>") == 0);
	new_file = process_operator(token, is_heredoc, is_append);
	if (new_file)
	{
		add_file_to_cmd(new_cmd, new_file, is_input);
		*token = (*token)->next;
		return (1);
	}
	return (0);
}

int	process_token(t_cmd *new_cmd, t_token **token, int *i)
{
	skip_spaces(token);
	if (!*token || ft_strcmp((*token)->type, "pipe") == 0)
		return (1);
	if (ft_strcmp((*token)->type, "command") == 0 || ft_strcmp((*token)->type,
			"argument") == 0)
	{
		return (process_command_or_argument(new_cmd, token, i));
	}
	else if (ft_strcmp((*token)->type, "operator") == 0)
	{
		return (process_operator_token(new_cmd, token));
	}
	free(new_cmd->cmd);
	return (0);
}
