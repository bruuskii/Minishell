/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:45:54 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/28 11:57:12 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_env_node(t_env **head, t_env *nodetodelete)
{
	if ((*head) == NULL || nodetodelete == NULL)
	{
		return ;
	}
	if ((*head) == nodetodelete)
	{
		(*head) = nodetodelete->next;
		if ((*head) != NULL)
			(*head)->prev = NULL;
	}
	if (nodetodelete->next != NULL)
	{
		nodetodelete->next->prev = nodetodelete->prev;
	}
	if (nodetodelete->prev != NULL)
	{
		nodetodelete->prev->next = nodetodelete->next;
	}
	if (nodetodelete->line)
		free(nodetodelete->line);
	if (nodetodelete)
		free(nodetodelete);
}

void	delete_token_node(t_token **head, t_token *nodetodelete)
{
	if ((*head) == NULL || nodetodelete == NULL)
	{
		return ;
	}
	if ((*head) == nodetodelete)
	{
		(*head) = nodetodelete->next;
		if ((*head) != NULL)
			(*head)->prev = NULL;
	}
	if (nodetodelete->next != NULL)
	{
		nodetodelete->next->prev = nodetodelete->prev;
	}
	if (nodetodelete->prev != NULL)
	{
		nodetodelete->prev->next = nodetodelete->next;
	}
	if (nodetodelete->token)
		free(nodetodelete->token);
	if (nodetodelete->type)
		free(nodetodelete->type);
	if (nodetodelete)
		free(nodetodelete);
}

void	delete_cmd_node(t_cmd **head, t_cmd *nodetodelete)
{
	t_cmd	*current;

	current = (*head);
	if ((*head) == NULL || nodetodelete == NULL)
		return ;
	if ((*head) == nodetodelete)
		(*head) = nodetodelete->next;
	else
	{
		while (current->next && current->next != nodetodelete)
			current = current->next;
	}
	if (current->next)
		current->next = nodetodelete->next;
	free_db_arr(nodetodelete->cmd);
	delete_fd_nodes(&nodetodelete->outfile);
	delete_fd_nodes(&nodetodelete->infile);
	
	if (nodetodelete)
		free(nodetodelete);
}

void	delete_fd_node(t_filedescriptiom **head,
		t_filedescriptiom *nodetodelete)
{
	t_filedescriptiom	*current;

	current = (*head);
	if ((*head) == NULL || nodetodelete == NULL)
	{
		return ;
	}
	if ((*head) == nodetodelete)
		(*head) = nodetodelete->next;
	else
	{
		while (current->next && current->next != nodetodelete)
			current = current->next;
	}
	if (current->next)
		current->next = nodetodelete->next;
	if (nodetodelete->delimeter)
		free(nodetodelete->delimeter);
	if (nodetodelete->filename)
		free(nodetodelete->filename);
	if (nodetodelete)
		free(nodetodelete);
}

void	free_exec(int isexit)
{
	delete_cmds_node();
	if (g_exec->paths)
		free_db_arr(g_exec->paths);
	if (isexit)
	{
		delete_env();
		if (g_exec)
			free(g_exec);
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	}
}
