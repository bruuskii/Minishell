/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 02:26:04 by ainouni           #+#    #+#             */
/*   Updated: 2024/07/17 11:32:58 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	free_paths(char **paths)
// {
// 	int	i;

// 	if (!paths)
// 		return ;
// 	i = 0;
// 	while (paths[i])
// 	{
// 		free(paths[i]);
// 		i++;
// 	}
// }

// static char	*get_pathline_from_env(char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (!ft_strncmp("PATH=", env[i], 5))
// 		{
// 			return (env[i] + 5);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

char	*get_path(t_exec *exec, char *cmd)
{
	char	*path;
	int		i = 0;

	while (exec->Paths[i])
	{
		path = ft_strjoin(exec->Paths[i], "/");
		path = ft_strjoin(path, cmd);
		if (access(path, F_OK) == 0)
		{
			return (path);
		}
		else
		{
			if (*path)
				free(path);
		}
		i++;
	}
	return (NULL);
}
