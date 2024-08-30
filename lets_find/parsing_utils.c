/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:59:39 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 18:15:48 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_string_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->token);
		free(tmp);
	}
}

t_token	*create_new_token(char *token_str, int args_nbr)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token = ft_strdup(token_str);
	if (!new_token->token)
	{
		free(new_token);
		return (NULL);
	}
	new_token->next = NULL;
	new_token->prev = NULL;
	new_token->nbr_of_args = args_nbr;
	return (new_token);
}

void	update_args_and_command(t_token *current, int index, int *args_nbr,
		int *is_command)
{
	if (ft_strcmp(current->type, "pipe") != 0 && index != 0
		&& ft_strcmp(current->type, "argument") == 0)
	{
		(*args_nbr)++;
		current->nbr_of_args = *args_nbr;
	}
	if (ft_strcmp(current->type, "pipe") == 0)
	{
		*is_command = 1;
		*args_nbr = 0;
	}
	else
		*is_command = 0;
}

void	processs_token(t_token *current, t_env *env, char **tokens, int index)
{
	static int	args_nbr = 0;
	static int	is_command = 1;
	char		*processed_token;

	grep_type(current, index, is_command);
	expand(current, env, tokens, index);
	processed_token = double_quotes(current->token);
	if (processed_token)
	{
		free(current->token);
		current->token = processed_token;
	}
	update_args_and_command(current, index, &args_nbr, &is_command);
}
