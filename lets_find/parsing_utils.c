/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_username <your_email@student.42.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:00:00 by your_username    #+#    #+#             */
/*   Updated: 2023/08/18 10:00:00 by your_username   ###   ########.fr       */
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

void	link_tokens(t_token **head, t_token **current, t_token *new_token)
{
	if (*current)
		(*current)->next = new_token;
	else
		*head = new_token;
	new_token->prev = *current;
	*current = new_token;
}

t_token	*tokenize_input_helper(char **tokens, t_env *env)
{
	int		index;
	t_token	*head;
	t_token	*current;
	t_token	*new_token;

	index = 0;
	head = NULL;
	current = NULL;
	while (tokens && tokens[index])
	{
		new_token = create_new_token(tokens[index], 0);
		if (!new_token)
		{
			free_tokens(head);
			return (NULL);
		}
		link_tokens(&head, &current, new_token);
		processs_token(current, env, tokens, index);
		index++;
	}
	return (head);
}
