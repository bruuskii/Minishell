/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:08:34 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/26 19:29:14 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(char *cmd)
{
	ft_export2(cmd, getequalindex(cmd));
}

int	check_syntax(char *cmd)
{
	int	i;
	int	equalfound;

	i = 0;
	equalfound = 0;
	if (ft_isspace(cmd[i]) || ft_isdigit(cmd[i]) || !strncmp(cmd, "=",
			strlen(cmd)))
		return (0);
	while (cmd[i])
	{
		if (!(ft_isalnum(cmd[i]) || cmd[i] == '_' || cmd[i] == '+'
				|| cmd[i] == '=' || cmd[i] == '$') && !equalfound)
			return (0);
		if (cmd[i] == '+' && (cmd[i + 1] == '\0' || cmd[i + 1] != '=')
			&& !equalfound)
			return (0);
		if (cmd[i] == '=')
		{
			equalfound = 1;
			if (ft_isspace(cmd[i + 1]))
				return (0);
		}
		i++;
	}
	return (1);
}

void	print_env_export(t_env *env_export)
{
	t_env	*temp;

	temp = env_export;
	while (temp)
	{
		printf("declare -x %s\n", temp->line);
		temp = temp->next;
	}
}

void	export(char **cmd)
{
	int	i;

	i = 1;
	if (!cmd[1])
	{
		print_env(g_exec->env, 1);
		return ;
	}
	while (cmd[i])
	{
		if (check_syntax(cmd[i]))
			ft_export(cmd[i]);
		else
		{
			printf("%s not a valid identifier\n", cmd[i]);
			g_exec->exit_status = 1;
		}
		i++;
	}
}
