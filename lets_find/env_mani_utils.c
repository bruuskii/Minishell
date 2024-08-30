/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mani_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:51:53 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:13:49 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node(char *str)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->line = ft_strdup(str);
	if (!node->line)
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	free_env_list(t_env *head)
{
	t_env	*current;

	while (head)
	{
		current = head;
		head = head->next;
		free(current->line);
		free(current);
	}
}

t_env	*add_env_node(t_env **head, t_env **prev, char *str)
{
	t_env	*current;

	current = create_env_node(str);
	if (!current)
	{
		free_env_list(*head);
		return (NULL);
	}
	if (!*head)
		*head = current;
	if (*prev)
	{
		(*prev)->next = current;
		current->prev = *prev;
	}
	*prev = current;
	return (current);
}

void	printf_dq_after(char *cmd, char c)
{
	int	i;
	int	isfirst;

	i = 0;
	isfirst = 1;
	while (cmd[i])
	{
		ft_putchar_fd(cmd[i], 1);
		if (cmd[i] == c && isfirst)
		{
			ft_putchar_fd('"', 1);
			isfirst = 0;
		}
		i++;
	}
	if (!isfirst)
		ft_putchar_fd('"', 1);
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
