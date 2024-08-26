/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils00.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:45:41 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/26 18:56:34 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_with_message(char *s, int exit_value)
{
	ft_putstr_fd(s, 2);
	exit(exit_value);
}

int	itsbuiltin(t_cmd *cmd)
{
	if (!cmd->cmd[0])
		return (0);
	if (!ft_strcmp(cmd->cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
		return (1);
	else
		return (0);
}

void	ft_exec_no_path(t_cmd *cmd, char **env, char *commandpath)
{
	commandpath = get_path(cmd->cmd[0]);
	if (!commandpath)
	{
		ft_putstr_fd(cmd->cmd[0], 2);
		exit_with_message(": command path not found\n", 127);
	}
	if (execve(commandpath, cmd->cmd, env) == -1)
	{
		free(commandpath);
		free_db_arr(env);
		exit_with_message("execve error\n", 127);
	}
}

void	ft_exec(t_cmd *cmd)
{
	char	*commandpath;
	char	**envtemp;

	if (!cmd->cmd[0])
		return ;
	commandpath = NULL;
	envtemp = init_env_arr();
	if (!ft_strchr(cmd->cmd[0], '/'))
	{
		ft_exec_no_path(cmd, envtemp, commandpath);
	}
	else
	{
		if (execve(cmd->cmd[0], cmd->cmd, envtemp) == -1)
		{
			exit_with_message("execve error\n", 127);
			free_db_arr(envtemp);
		}
	}
}

void	ft_exec_builtin(t_cmd *cmd)
{
	if (!cmd->cmd[0])
		return ;
	if (!ft_strcmp(cmd->cmd[0], "echo"))
		echo(cmd->cmd);
	else if (!ft_strcmp(cmd->cmd[0], "cd"))
		cd(cmd->cmd);
	if (!ft_strcmp(cmd->cmd[0], "pwd"))
		pwd();
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		export(cmd->cmd);
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		unset(cmd->cmd);
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		print_env(g_exec->env, 0);
	else if (!strcmp(cmd->cmd[0], "exit"))
		ft_exit(cmd->cmd);
}
