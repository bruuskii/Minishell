/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:06:39 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/26 19:07:34 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("pwd: error retrieving current directory\n",
			STDOUT_FILENO);
		g_exec->exit_status = 1;
	}
	else
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		g_exec->exit_status = 0;
	}
	if (cwd)
		free(cwd);
}
