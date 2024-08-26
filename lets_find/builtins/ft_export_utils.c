/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:19:53 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/26 19:28:18 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	insertatend(t_env **head, t_env *node_to_add)
{
	t_env	*temp;

	temp = NULL;
	if (!(*head))
	{
		(*head) = node_to_add;
		return ;
	}
	temp = (*head);
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = node_to_add;
	node_to_add->prev = temp;
	node_to_add->next = NULL;
}

t_env	*is_in_env(t_env *env, char *value_to_check)
{
	t_env	*temp;
	char	*check_with;
	int		i;

	temp = env;
	i = 0;
	while (temp)
	{
		i = getequalindex(temp->line);
		check_with = malloc(i + 1);
		if (!check_with)
			return (NULL);
		ft_strlcpy(check_with, temp->line, i + 1);
		if (!strncmp(check_with, value_to_check, strlen(value_to_check) + 1))
		{
			free(check_with);
			return (temp);
		}
		free(check_with);
		temp = temp->next;
	}
	return (NULL);
}

char	*remove_char_(char *str, char c)
{
	char	*s;
	int		i;
	int		j;
	int		isfirstplusfound;

	i = 0;
	j = 0;
	isfirstplusfound = 0;
	s = malloc(ft_strlen(str) + 1);
	if (!s || !str)
		return (NULL);
	while (str[i])
	{
		if (str[i] != c || isfirstplusfound)
		{
			s[j] = str[i];
			j++;
		}
		else
			isfirstplusfound = 1;
		i++;
	}
	if (str)
		free(str);
	return (s[j] = '\0', s);
}

int	getequalindex(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd[i])
	{
		if (cmd[i] == '+' || cmd[i] == '=')
			break ;
		i++;
	}
	return (i);
}
