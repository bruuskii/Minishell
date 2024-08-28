/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:08:57 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/28 12:00:36 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_in_env(t_env *temp, char *word_to_app, int isappend, char *cmd)
{
	if (isappend)
	{
		if (!ft_strchr(temp->line, '='))
			temp->line = ft_strjoin2(temp->line, "=");
		temp->line = ft_strjoin2(temp->line, word_to_app);
	}
	else
	{
		if (ft_strchr(cmd, '='))
		{
			free(temp->line);
			temp->line = ft_strdup(cmd);
		}
	}
}

void	add_to_env(t_env *temp, int isappend, char *cmd)
{
	temp = (t_env *)malloc(sizeof(t_env));
	if (isappend)
		temp->line = remove_char_(ft_strdup(cmd), '+');
	else
		temp->line = ft_strdup(cmd);
	temp->next = NULL;
	insertatend(&g_exec->env, temp);
}

void	ft_export2(char *cmd, int indexofequal)
{
	char	*value_to_check;
	t_env	*temp;
	int		isappend;
	char	*word_to_app;

	value_to_check = malloc(indexofequal + 1);
	ft_strlcpy(value_to_check, cmd, indexofequal + 1);
	temp = is_in_env(g_exec->env, value_to_check);
	word_to_app = NULL;
	isappend = 0;
	if (cmd[indexofequal] == '+')
	{
		isappend = 1;
		word_to_app = ft_strdup(&cmd[indexofequal + 2]);
	}
	if (temp)
		update_in_env(temp, word_to_app, isappend, cmd);
	else
		add_to_env(temp, isappend, cmd);
	if (word_to_app)
		free(word_to_app);
	if (value_to_check)
		free(value_to_check);
}
