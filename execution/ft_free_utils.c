/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:45:51 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/28 11:57:29 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_env(void)
{
	t_env	*env;
	t_env	*tmp;

	env = g_exec->env;
	while (env)
	{
		tmp = env;
		env = env->next;
		delete_env_node(&g_exec->env, tmp);
	}
}

void	free_db_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr != NULL)
	{
		while (arr[i])
		{
			if (arr[i])
				free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void	delete_cmds_node(void)
{
	t_cmd	*tmp;
	t_cmd	*cmd;

	cmd = g_exec->cmd;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		delete_cmd_node(&g_exec->cmd, tmp);
	}
}

void	delete_tokens(void)
{
	t_token	*token;
	t_token	*tmp;

	token = g_exec->tokens;
	while (token)
	{
		tmp = token;
		token = token->next;
		delete_token_node(&g_exec->tokens, tmp);
	}
}

void	delete_fd_nodes(t_filedescriptiom **src)
{
	t_filedescriptiom	*tmp;
	t_filedescriptiom	*fd;

	fd = (*src);
	while (fd)
	{
		tmp = fd;
		fd = fd->next;
		delete_fd_node(src, tmp);
	}
}
