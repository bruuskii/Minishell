/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_username <your_email@student.42.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:00:00 by your_username    #+#    #+#             */
/*   Updated: 2023/08/18 10:00:00 by your_username   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_and_parse(char **tokens, t_env *env, t_token **head, t_cmd **cmd)
{
	*head = tokenize_input(tokens, env);
	if (!(*head))
		return (0);
	*cmd = parse_every_command(*head);
	if (!(*cmd))
	{
		free(*cmd);
		return (0);
	}
	return (1);
}

int	process_tokens(char *str, t_env *env, t_token **token, t_cmd **cmd)
{
	char	**tokens;
	t_token	*head;

	tokens = split_string(str);
	if (!tokens || !parse_every_word(tokens))
	{
		free_string_array(tokens);
		return (0);
	}
	if (!tokenize_and_parse(tokens, env, &head, cmd))
	{
		free_string_array(tokens);
		return (0);
	}
	free_string_array(tokens);
	free_tokens(head);
	*token = NULL;
	return (1);
}

int	print_type(char *str, t_env *env, t_token **token, t_cmd **cmd)
{
	*token = NULL;
	*cmd = NULL;
	if (!str || !first_parse(str))
		return (0);
	return (process_tokens(str, env, token, cmd));
}

void	handle_quotes_and_args(t_token *current, int *args_nbr, int index)
{
	char	*processed_token;

	processed_token = double_quotes(current->token);
	if (processed_token)
	{
		free(current->token);
		current->token = processed_token;
	}
	if (ft_strcmp(current->type, "pipe") != 0 && index != 0
		&& ft_strcmp(current->type, "argument") == 0)
	{
		(*args_nbr)++;
		current->nbr_of_args = *args_nbr;
	}
}

void	update_command_status(t_token *current, int *is_command,
		int *args_nbr)
{
	if (ft_strcmp(current->type, "pipe") == 0)
	{
		*is_command = 1;
		*args_nbr = 0;
	}
	else
		*is_command = 0;
}
