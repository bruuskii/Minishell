/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:45:45 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/30 20:41:00 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_pipes(t_cmd *cmd)
{
	int		i;
	t_cmd	*temp;

	i = 0;
	temp = cmd;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	if (i)
		return (i - 1);
	return (i);
}

int	countfiles(t_filedescriptiom *files)
{
	t_filedescriptiom	*filetmp;
	int					i;

	if (files == NULL)
	{
		return (0);
	}
	filetmp = files;
	i = 0;
	while (filetmp)
	{
		i++;
		filetmp = filetmp->next;
	}
	return (i);
}

char	**get_paths(void)
{
	char	**paths;

	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		return (NULL);
	return (paths);
}
