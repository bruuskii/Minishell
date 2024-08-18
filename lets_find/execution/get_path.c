/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 02:26:04 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/18 15:41:57 by izouine          ###   ########.fr       */
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
