/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mani.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:25:17 by izouine           #+#    #+#             */
/*   Updated: 2024/08/31 11:36:22 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_old_pwd(t_env *env)
{
	char	*pwd;

	pwd = find_pwd(env);
	if (pwd)
		update_oldpwd(env, pwd);
}

void	save_current_pwd(t_env *env)
{
	char	pwd[1024];
	char	*new_pwd;
	t_env	*current;

	if (!getcwd(pwd, sizeof(pwd)))
		return ;
	current = env;
	while (current)
	{
		if (ft_strncmp(current->line, "PWD=", 4) == 0)
		{
			free(current->line);
			new_pwd = ft_strjoin("PWD=", pwd);
			current->line = new_pwd;
			return ;
		}
		current = current->next;
	}
}
