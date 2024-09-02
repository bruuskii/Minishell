/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:05:21 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/26 19:06:00 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_char(char *cmd, char c)
{
	int	count;

	if (!cmd || !c)
		return (0);
	count = 0;
	while (*cmd)
	{
		if (*cmd == c)
			count++;
		cmd++;
	}
	return (count);
}

void	ft_echo(char **cmd, int wordfound, int i, int iswith_nl)
{
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], "-n", 2) && !wordfound)
		{
			if (count_char(cmd[i], '-') > 1)
			{
				printf("%s", cmd[i]);
				wordfound = 1;
			}
			else
				iswith_nl = 0;
		}
		else
		{
			printf("%s", cmd[i]);
			wordfound = 1;
		}
		i++;
	}
	if (iswith_nl)
		printf("\n");
	g_exec->exit_status = 0;
}

void	echo(char **cmd)
{
	int	i;
	int	iswith_nl;
	int	wordfound;

	if (!cmd[1])
	{
		write(1, "\n", 1);
		return ;
	}
	i = 1;
	iswith_nl = 1;
	wordfound = 0;
	ft_echo(cmd, wordfound, i, iswith_nl);
}
