/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 02:26:04 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/05 12:28:07 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"




void	free_db_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}



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

	g_exec->Paths = envpath_to_arr();
	while (g_exec->Paths[i])
	{
		path = ft_strjoin(g_exec->Paths[i], "/");
		path = ft_strjoin(path, cmd);
		if (access(path, F_OK) == 0)
		{
			free_db_arr(g_exec->Paths);
			return (path);
		}
		else
		{
			if (*path)
				free(path);
		}
		i++;
	}
	free_db_arr(g_exec->Paths);
	return (NULL);
}
