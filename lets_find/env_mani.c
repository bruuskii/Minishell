/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mani.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:25:17 by izouine           #+#    #+#             */
/*   Updated: 2024/08/18 15:31:49 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*create_env_node(char *str)
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

static void	free_env_list(t_env *head)
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

static t_env	*add_env_node(t_env **head, t_env **prev, char *str)
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

static void	update_shlvl(t_env *env, const char *shlvl_prefix)
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

static char	*find_pwd(t_env *env)
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

static void	update_oldpwd(t_env *env, char *pwd)
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
	char pwd[1024];
	char *new_pwd;
	t_env *current;

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