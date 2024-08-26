/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:45:38 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/26 18:57:15 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_parent(t_exec_utils *exec_utils, t_cmd *cmd, t_cmd *prev)
{
	if (exec_utils->its_builtin && !cmd->next && !prev)
	{
		if (exec_utils->fdout != STDOUT_FILENO)
		{
			dup2(exec_utils->fdout, STDOUT_FILENO);
			close(exec_utils->fdout);
			ft_exec_builtin(cmd);
			dup2(exec_utils->savedout, STDOUT_FILENO);
			close(exec_utils->savedout);
		}
		else
			ft_exec_builtin(cmd);
	}
	if (exec_utils->fdin != STDIN_FILENO)
		close(exec_utils->fdin);
	if (prev)
	{
		close(prev->fd[0]);
		close(prev->fd[1]);
	}
}

void	execute_child(t_exec_utils *exec_utils, t_cmd *cmd, t_cmd *prev)
{
	set_upfdfiles(exec_utils->fdin, exec_utils->fdout, cmd, prev);
	if (!exec_utils->its_builtin)
		ft_exec(cmd);
	else if (!ft_strcmp(cmd->cmd[0], "pwd") && !cmd->next)
		exit(EXIT_SUCCESS);
	else if (exec_utils->its_builtin && !cmd->cmd[1])
		ft_exec_builtin(cmd);
	exit(EXIT_SUCCESS);
}

void	ft_execute(t_exec_utils *exec_utils, t_cmd *cmd, t_cmd *prev)
{
	if (cmd->next)
	{
		cmd->fd = malloc(2 * sizeof(int));
		if (pipe(cmd->fd) == -1)
		{
			perror("pipe error\n");
			exit(EXIT_FAILURE);
		}
	}
	exec_utils->its_builtin = itsbuiltin(cmd);
	exec_utils->pid = fork();
	if (exec_utils->pid == -1)
		exit(EXIT_FAILURE);
	if (exec_utils->pid == 0)
		execute_child(exec_utils, cmd, prev);
	else
		execute_parent(exec_utils, cmd, prev);
}

void	get_exitstatus(t_exec_utils exec_utils)
{
	int	j;
	int	status;

	j = -1;
	while (++j <= exec_utils.countpipes)
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			if (!exec_utils.its_builtin)
				g_exec->exit_status = WEXITSTATUS(status);
		}
		else
			printf("Child process did not terminate normally\n");
	}
	if (exec_utils.exit_state == 130)
		g_exec->exit_status = 130;
	else if (exec_utils.sig_rec == 3)
		g_exec->exit_status = 0;
}

t_exec_utils	init_exec_utils(t_cmd *cmd)
{
	t_exec_utils	exec_utils;

	exec_utils.countpipes = count_pipes(cmd);
	exec_utils.i = 0;
	exec_utils.fdin = -1;
	exec_utils.savedout = dup(STDOUT_FILENO);
	exec_utils.fdout = -1;
	exec_utils.file = NULL;
	exec_utils.exit_state = 0;
	exec_utils.sig_rec = 0;
	return (exec_utils);
}
