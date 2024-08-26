/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:45:18 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/26 19:19:19 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exec	*initexec(char **env)
{
	t_exec	*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->env = init_env(env);
	exec->paths = NULL;
	exec->cmd = NULL;
	exec->exit_status = 0;
	exec->herdoc_sig = 0;
	return (exec);
}

void	advance_cmd(t_cmd *cmd, t_cmd *prev, t_exec_utils *exec_utils)
{
	prev = cmd;
	cmd = cmd->next;
	exec_utils->i++;
	g_exec->exit_status = 1;
}

void	execute(t_exec *exec)
{
	t_cmd			*cmd;
	t_cmd			*prev;
	t_exec_utils	exec_utils;

	cmd = exec->cmd;
	prev = NULL;
	exec_utils = init_exec_utils(cmd);
	while (cmd && exec_utils.i <= exec_utils.countpipes)
	{
		exec_utils.fdin = getinputfile(cmd, &exec_utils);
		exec_utils.fdout = getoutputfile(cmd, &exec_utils);
		if (exec_utils.sig_rec)
			break ;
		if (exec_utils.fdin == -1 || exec_utils.fdout == -1)
		{
			advance_cmd(cmd, prev, &exec_utils);
			continue ;
		}
		ft_execute(&exec_utils, cmd, prev);
		prev = cmd;
		cmd = cmd->next;
		exec_utils.i++;
	}
	get_exitstatus(exec_utils);
	free_exec(0);
}
// void free_filedescriptiom(t_filedescriptiom *file)
// {
//     t_filedescriptiom *current;
//     t_filedescriptiom *next;

//     fprintf(stderr, "Entering free_filedescriptiom\n");
//     current = file;
//     while (current)
//     {
//         fprintf(stderr, "Processing filedescriptiom: %p\n", (void*)current);
//         next = current->next;
//         if (current->filename)
//         {
//             fprintf(stderr, "Freeing filename: %p\n",
// (void*)current->filename);
//             free(current->filename);
//         }
//         if (current->delimeter)
//         {
//             fprintf(stderr, "Freeing delimeter: %p\n",
// (void*)current->delimeter);
//             free(current->delimeter);
//         }
//         if (!current->isherdoc)  // Only free non-heredoc descriptors
//         {
//             fprintf(stderr, "Freeing non-heredoc filedescriptiom: %p\n",
// (void*)current);
//             free(current);
//         }
//         else
//         {
//             fprintf(stderr, "Skipping heredoc filedescriptiom: %p\n",
// (void*)current);
//         }
//         current = next;
//     }
//     fprintf(stderr, "Exiting free_filedescriptiom\n");
// }

// void free_cmd(t_cmd *cmd)
// {
//     if (!cmd || !cmd->cleanup_ready)
//     {
//         return ; // Don't free if not ready for cleanup
//     }
//     int i;

//     fprintf(stderr, "Entering free_cmd for cmd: %p\n", (void*)cmd);
//     if (!cmd)
//     {
//         fprintf(stderr, "cmd is NULL, exiting free_cmd\n");
//         return ;
//     }

//     fprintf(stderr, "Freeing cmd->cmd\n");
//     if (cmd->cmd)
//     {
//         for (i = 0; cmd->cmd[i]; i++)
//         {
//             fprintf(stderr, "Freeing cmd->cmd[%d]: %p\n", i,
// (void*)cmd->cmd[i]);
//             free(cmd->cmd[i]);
//         }
//         fprintf(stderr, "Freeing cmd->cmd array itself\n");
//         free(cmd->cmd);
//         cmd->cmd = NULL;
//     }
//     else
//     {
//         fprintf(stderr, "cmd->cmd is NULL\n");
//     }

//     fprintf(stderr, "Checking cmd->infile: %p\n", (void*)cmd->infile);
//     if (cmd->infile)
//     {
//         fprintf(stderr, "Freeing cmd->infile\n");
//         free_filedescriptiom(cmd->infile);
//         cmd->infile = NULL;
//     }
//     else
//     {
//         fprintf(stderr, "cmd->infile is NULL\n");
//     }

//     fprintf(stderr, "Checking cmd->outfile: %p\n", (void*)cmd->outfile);
//     if (cmd->outfile)
//     {
//         fprintf(stderr, "Freeing cmd->outfile\n");
//         free_filedescriptiom(cmd->outfile);
//         cmd->outfile = NULL;
//     }
//     else
//     {
//         fprintf(stderr, "cmd->outfile is NULL\n");
//     }

//     fprintf(stderr, "Checking cmd->fd: %p\n", (void*)cmd->fd);
//     if (cmd->fd && cmd->fd != (int *)0xbebebebebebebebe)
//     {
//         fprintf(stderr, "Freeing cmd->fd\n");
//         if (cmd->fd[0] != -1)
//         {
//             fprintf(stderr, "Closing cmd->fd[0]: %d\n", cmd->fd[0]);
//             close(cmd->fd[0]);
//         }
//         if (cmd->fd[1] != -1)
//         {
//             fprintf(stderr, "Closing cmd->fd[1]: %d\n", cmd->fd[1]);
//             close(cmd->fd[1]);
//         }
//         free(cmd->fd);
//     }
//     else
//     {
//         fprintf(stderr, "cmd->fd is NULL or invalid\n");
//     }
//     cmd->fd = NULL;

//     fprintf(stderr, "Freeing cmd itself\n");
//     free(cmd);
//     fprintf(stderr, "Exiting free_cmd\n");
// }

// void cleanup_commands(t_cmd *cmd_head)
// {
//     t_cmd *current;
//     t_cmd *next;

//     fprintf(stderr, "Entering cleanup_commands\n");
//     current = cmd_head;
//     while (current)
//     {
//         fprintf(stderr, "Processing cmd: %p\n", (void*)current);
//         next = current->next;
//         free_cmd(current);
//         current = next;
//     }
//     fprintf(stderr, "Exiting cleanup_commands\n");
// }