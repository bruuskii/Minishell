/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:15:00 by izouine           #+#    #+#             */
/*   Updated: 2024/08/22 12:30:00 by assistant        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*init_new_cmd(void)
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

static int	count_args(t_token *token)
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

static t_filedescriptiom	*create_file_desc(t_token *token)
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

static void	add_file_to_cmd(t_cmd *cmd, t_filedescriptiom *new_file,
		int is_infile)
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

static int	process_token(t_cmd *new_cmd, t_token **token, int *i)
{
	int					is_heredoc;
	int					is_input;
	int					is_append;
	t_filedescriptiom	*new_file;

	while (*token && ft_strcmp((*token)->type, "space") == 0)
		*token = (*token)->next;
	if (!*token || ft_strcmp((*token)->type, "pipe") == 0)
		return (1);
	if (ft_strcmp((*token)->type, "command") == 0 || ft_strcmp((*token)->type,
			"argument") == 0)
	{
		new_cmd->cmd[(*i)++] = ft_strdup((*token)->token);
	}
	else if (ft_strcmp((*token)->type, "operator") == 0)
	{
		is_heredoc = (ft_strcmp((*token)->token, "<<") == 0);
		is_input = (ft_strcmp((*token)->token, "<") == 0 || is_heredoc);
		is_append = (ft_strcmp((*token)->token, ">>") == 0);
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
				add_file_to_cmd(new_cmd, new_file, is_input);
			}
			else
			{
				return (0); // Memory allocation failed
			}
		}
		else
		{
			free(new_cmd->cmd);
			return (0); // Expected file or delimiter not found
		}
	}
	else
	{
		return (0); // Unexpected token type
	}
	*token = (*token)->next;
	return (1);
}

static t_cmd	*parse_command(t_token **token)
{
	t_cmd	*new_cmd;
	int		nbr_of_args;
	int		i;

	new_cmd = init_new_cmd();
	if (!new_cmd)
	{
		free(new_cmd);
		return (NULL);
	}
	nbr_of_args = count_args(*token);
	new_cmd->cmd = (char **)malloc((nbr_of_args + 1) * sizeof(char *));
	if (!new_cmd->cmd)
	{
		free(new_cmd->cmd);
		free(new_cmd);
		return (NULL);
	}
	i = 0;
	while (*token && ft_strcmp((*token)->type, "pipe") != 0)
	{
		if (!process_token(new_cmd, token, &i))
		{
			// Clean up and return NULL on error
			// TODO: Add a function to free the t_cmd structure
			free(new_cmd->cmd);
			free(new_cmd);
			return (NULL);
		}
	}
	new_cmd->cmd[i] = NULL;
	return (new_cmd);
}

t_cmd	*parse_every_command(t_token *token)
{
	t_cmd *cmd_head;
	t_cmd *cmd_current;
	t_cmd *new_cmd;

	cmd_head = NULL;
	cmd_current = NULL;
	while (token)
	{
		new_cmd = parse_command(&token);
		if (!new_cmd)
		{
			// TODO: Add cleanup for previously allocated commands
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