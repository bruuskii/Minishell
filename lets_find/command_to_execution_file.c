/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_execution_file.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:34:36 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:09:34 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
