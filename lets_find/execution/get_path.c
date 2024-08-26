/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 02:26:04 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/26 17:01:58 by ainouni          ###   ########.fr       */
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
	int		i;

	i = 0;
	g_exec->paths = envpath_to_arr();
	if (!g_exec->paths)
		return (NULL);
	while (g_exec->paths[i])
	{
		path = ft_strjoin(g_exec->paths[i], "/");
		path = ft_strjoin2(path, cmd);
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



void	copy_env_in_arr(char **arr, t_env *tmp)
{
	int i;

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
}

char	**init_env_arr()
{
	int 	i;
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
	copy_env_in_arr(arr, tmp);
	arr[i] = NULL;
	return (arr);
}

