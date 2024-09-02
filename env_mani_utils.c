/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mani_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:36:43 by izouine           #+#    #+#             */
/*   Updated: 2024/08/31 12:04:45 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env, int isexport)
{
	while (env)
	{
		if (env->line)
		{
			if (isexport)
			{
				ft_putstr_fd("declare -x ", 1);
				printf_dq_after(env->line, '=');
				ft_putchar_fd('\n', 1);
			}
			else if (ft_strchr(env->line, '='))
			{
				ft_putendl_fd(env->line, 1);
			}
		}
		env = env->next;
	}
}

void	update_shlvl(t_env *env, const char *shlvl_prefix)
{
	int		shlvl_value;
	char	*new_shlvl;
	char	*value_str;

	shlvl_value = ft_atoi(env->line + ft_strlen(shlvl_prefix)) + 1;
	value_str = ft_itoa(shlvl_value);
	new_shlvl = ft_strjoin(shlvl_prefix, value_str);
	free(value_str);
	free(env->line);
	env->line = new_shlvl;
}

void	increment_shell_level(t_env *env)
{
	t_env		*current;
	const char	*shlvl_prefix;

	shlvl_prefix = "SHLVL=";
	current = env;
	while (current)
	{
		if (ft_strncmp(current->line, shlvl_prefix,
				ft_strlen(shlvl_prefix)) == 0)
		{
			update_shlvl(current, shlvl_prefix);
			return ;
		}
		current = current->next;
	}
	current = create_env_node("SHLVL=1");
	if (current)
	{
		current->next = env;
		if (env)
			env->prev = current;
		env = current;
	}
}

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
