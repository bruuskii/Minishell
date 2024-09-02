/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:07:50 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/26 19:08:04 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(char **cmd)
{
	t_env	*env;
	int		i;

	if (!cmd[1])
		return ;
	i = 1;
	while (cmd[i])
	{
		env = is_in_env(g_exec->env, cmd[i]);
		if (env)
			delete_env_node(&g_exec->env, env);
		i++;
	}
}
