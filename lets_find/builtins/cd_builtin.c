/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:04:08 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/26 19:05:10 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_home(void)
{
	t_env	*tmpenv;
	int		value;

	tmpenv = is_in_env(g_exec->env, "HOME");
	if (!tmpenv)
	{
		ft_putstr_fd("faild to change directory\n", 2);
		g_exec->exit_status = 1;
	}
	else
	{
		value = chdir(tmpenv->line + 5);
		if (value != 0)
		{
			ft_putstr_fd("cd faild to change directory", 2);
			g_exec->exit_status = 1;
		}
		else
		{
			g_exec->exit_status = 0;
			save_old_pwd(g_exec->env);
			save_current_pwd(g_exec->env);
		}
	}
}

void	cd_path(char *path)
{
	char	*cwd;
	int		value;

	value = chdir(path);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("getcwd: cannot access parent directories\n", 2);
		g_exec->exit_status = 1;
		return ;
	}
	else if (value != 0)
	{
		ft_putstr_fd("chdir connot change directory\n", 2);
		g_exec->exit_status = 1;
		free(cwd);
		return ;
	}
	else
	{
		g_exec->exit_status = 0;
		save_old_pwd(g_exec->env);
		save_current_pwd(g_exec->env);
		free(cwd);
	}
}

void	cd_builtin(char **cmd)
{
	if (!cmd[1])
	{
		cd_home();
	}
	else
	{
		cd_path(cmd[1]);
	}
}

int	cd(char **cmd)
{
	if (cmd[1] && cmd[2])
	{
		g_exec->exit_status = 1;
		ft_putstr_fd("cd to many arguments AKhey\n", 2);
		return (0);
	}
	cd_builtin(cmd);
	return (1);
}
