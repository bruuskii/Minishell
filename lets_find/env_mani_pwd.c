/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mani_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:51:50 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:10:07 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_pwd(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strncmp(current->line, "PWD=", 4) == 0)
			return (current->line + 4);
		current = current->next;
	}
	return (NULL);
}

void	update_oldpwd(t_env *env, char *pwd)
{
	t_env	*current;
	char	*oldpwd;

	current = env;
	while (current)
	{
		if (ft_strncmp(current->line, "OLDPWD=", 7) == 0)
		{
			free(current->line);
			oldpwd = ft_strjoin("OLDPWD=", pwd);
			current->line = oldpwd;
			return ;
		}
		current = current->next;
	}
}

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
