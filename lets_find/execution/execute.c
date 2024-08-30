/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:45:18 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/30 20:43:32 by ainouni          ###   ########.fr       */
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

t_cmd	*advance_cmd(t_cmd *cmd, t_cmd *prev, t_exec_utils *exec_utils,
		int iserror)
{
	prev = cmd;
	cmd = cmd->next;
	exec_utils->i++;
	g_exec->exit_status = iserror;
	return (prev);
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
		exec_utils.fdout = getoutputfile(cmd);
		exec_utils.fdin = getinputfile(cmd, &exec_utils);
		if (exec_utils.exit_state == 130)
			break ;
		if (exec_utils.sig_rec)
			break ;
		if (exec_utils.fdin == -1 || exec_utils.fdout == -1)
		{
			prev = advance_cmd(cmd, prev, &exec_utils, 1);
			continue ;
		}
		ft_execute(&exec_utils, cmd, prev);
		advance_cmd(cmd, prev, &exec_utils, 0);
	}
	get_exitstatus(exec_utils);
	free_exec(0);
}
