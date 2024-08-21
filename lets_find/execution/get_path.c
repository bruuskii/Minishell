/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 02:26:04 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/21 00:55:54 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char **envpath_to_arr()
{
	t_env	*temp;
	char	**env_arr;

	temp = is_in_env(g_exec->env, "PATH");
	if (!temp)
		return (NULL);
	env_arr = ft_split((temp->line + 4), ':');
	if (!env_arr)
		return (NULL);
	return (env_arr);
}

char	*get_path(char *cmd)
{
	char	*path;
	int		i = 0;

	g_exec->paths = envpath_to_arr();
	if (!g_exec->paths)
		return (NULL);
	while (g_exec->paths[i])
	{
		path = ft_strjoin(g_exec->paths[i], "/");
		path = ft_strjoin(path, cmd);
		if (access(path, F_OK) == 0)
		{
			free_db_arr(g_exec->paths);
			return (path);
		}
		else
		{
			if (*path)
				free(path);
		}
		i++;
	}
	free_db_arr(g_exec->paths);
	return (NULL);
}


char	**init_env_arr()
{
	int i;
	t_env	*tmp;
	char	**arr;

	i = 0;
	tmp = g_exec->env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	arr = (char **) malloc ((i + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	tmp = g_exec->env;
	i = 0;
	while (tmp)
	{
		if (tmp->line)
		{
			arr[i] = ft_strdup(tmp->line);
			i++;
		}
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}


// void	update_env_arr()
// {
// 	int i = 0;
// 	t_env	*tmp = g_exec->env;

// 	while (tmp)
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	if (g_exec->env_arr != NULL)
// 		printf("no it's not null");
// 	g_exec->env_arr = (char **) malloc (i + 1);
// 	if (!g_exec->env_arr)
// 		return;
// 	tmp = g_exec->env;
// 	i = 0;
// 	while (tmp)
// 	{
// 		g_exec->env_arr[i] = ft_strdup(tmp->line);
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	g_exec->env_arr[i] = NULL;
// }
