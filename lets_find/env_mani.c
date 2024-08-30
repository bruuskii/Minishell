/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mani.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:25:17 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:06:24 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **str)
{
	t_env	*head;
	t_env	*previous;

	if (!str || !str[0])
		return (NULL);
	head = NULL;
	previous = NULL;
	while (*str)
	{
		if (!add_env_node(&head, &previous, *str))
			return (NULL);
		str++;
	}
	return (head);
}

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
