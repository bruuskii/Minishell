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

int	parse_every_word(char **tokens)
{
	int		index;
	char	current_quote;
	int		unclosed;

	current_quote = '\0';
	index = 0;
	unclosed = 0;
	while (tokens && tokens[index] != NULL)
	{
		unclosed = check_quotes(tokens[index], &current_quote);
		index++;
	}
	if (unclosed)
	{
		ft_putstr_fd("bash: unclosed quotes\n", 2);
		return (0);
	}
	return (1);
}

t_token	*tokenize_input(char **tokens, t_env *env)
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

int	print_type(char *str, t_env *env, t_token **token, t_cmd **cmd)
{
	char	**tokens;
	t_token	*head;

	*token = NULL;
	*cmd = NULL;
	if (!initialize_print_type(str, &tokens))
		return (0);
	head = tokenize_input(tokens, env);
	free_string_array(tokens);
	if (!head)
		return (0);
	if (!finalize_print_type(head, cmd))
		return (0);
	*token = NULL;
	return (1);
}
