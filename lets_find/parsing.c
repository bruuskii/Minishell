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

static void	process_quote(char c, char *current_quote)
{
	if (*current_quote == '\0')
	{
		if (c == '\'' || c == '"')
			*current_quote = c;
	}
	else if (c == *current_quote)
		*current_quote = '\0';
}

static int	check_quotes(char *token, char *current_quote)
{
	int	i;

<<<<<<< HEAD
    char **tokens = double_quotes(real_tokens);
    int index = 0;
    int args_nbr = 0;
    int is_command = 1;
    t_token *head = NULL;
    t_token *current = NULL;


    while (tokens && tokens[index]) {
        t_token *new_token = (t_token *)malloc(sizeof(t_token));
        if (!new_token) {
            // Free previously allocated tokens and return 0
            t_token *tmp = head;
            while (tmp) {
                t_token *next = tmp->next;
                free(tmp->token);
                free(tmp);
                tmp = next;
            }
            return 0;
        }

        new_token->token = strdup(tokens[index]);
        new_token->next = NULL;
        new_token->prev = current;
        new_token->nbr_of_args = args_nbr;
        if (current) {
            current->next = new_token;
        } else {
            head = new_token;
        }

        current = new_token;
        grep_type(current, index, is_command);

        expand(current, env, tokens, index);

        if (strcmp(current->type, "pipe") != 0 && index != 0 && strcmp(current->type, "argument") == 0) {
            args_nbr++;
            current->nbr_of_args = args_nbr;
        }

        if (strcmp(current->type, "pipe") == 0) {
            is_command = 1;
            printf("the number of these arguments %d\n", current->nbr_of_args);
            args_nbr = 0;
        } else {
            is_command = 0;
        }

        printf("token: %s, and type: %s\n", current->token, current->type);
        index++;
    }

    if( index > 0 && tokens[index - 1])
        printf("number of ac %d\n", current->nbr_of_args);
    current = head;

    (*cmd) = parse_every_command(current);
    index = 0;
    // while (tokens[index]) {
    //     if (strcmp(tokens[index], "cd") == 0) {
    //         if (tokens[index + 1]) {
    //             if (cd_builtin(tokens[index + 1], env) == 0) {
    //                 printf("cd: failed to change directory\n");
    //             }
    //             index++;
    //         } else {
    //             if (cd_builtin(NULL, env) == 0) {
    //                 printf("cd: failed to change directory\n");
    //             }
    //         }
    //     }
    //     index++;
    // }

    index = 0;
    while (tokens[index]) {
        free(tokens[index]);
        index++;
    }
    free(tokens);

    index = 0;
    while (real_tokens[index]) {
        free(real_tokens[index]);
        index++;
    }
    free(real_tokens);
    
    (*token) = head;
    return 1;
=======
	i = 0;
	while (token[i])
	{
		process_quote(token[i], current_quote);
		i++;
	}
	return (*current_quote != '\0');
>>>>>>> 0158cdf6b93864f77469af8767c1d3eb46d9c0ef
}

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

static t_token	*create_new_token(char *token_str, int args_nbr)
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

static void	update_args_and_command(t_token *current, int index,
				int *args_nbr, int *is_command)
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

static void	process_token(t_token *current, t_env *env, char **tokens,
				int index)
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

static void	link_tokens(t_token **head, t_token **current, t_token *new_token)
{
	if (*current)
		(*current)->next = new_token;
	else
		*head = new_token;
	new_token->prev = *current;
	*current = new_token;
}

static t_token	*tokenize_input_helper(char **tokens, t_env *env)
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
		process_token(current, env, tokens, index);
		index++;
	}
	return (head);
}

t_token	*tokenize_input(char **tokens, t_env *env)
{
	return (tokenize_input_helper(tokens, env));
}

int	print_type(char *str, t_env *env, t_token **token, t_cmd **cmd)
{
	char	**tokens;
	t_token	*head;

	if (!str || !first_parse(str))
		return (0);
	tokens = split_string(str);
	if (!tokens || !parse_every_word(tokens))
	{
		free_string_array(tokens);
		return (0);
	}
	head = tokenize_input(tokens, env);
	free_string_array(tokens);
	if (!head)
		return (0);
	(*cmd) = parse_every_command(head);
	if (!(*cmd))
	{
		free_tokens(head);
		return (0);
	}
	(*token) = head;
	return (1);
}

void	grep_type_space(t_token *token)
{
	t_token	*mine;

	if (ft_strcmp(token->prev->type, "command") == 0)
	{
		token->type = "argument";
		return ;
	}
	mine = token;
	while (mine->prev && ft_strcmp(mine->prev->token, "|") != 0)
		mine = mine->prev;
	if (ft_strcmp(mine->token, "|") == 0)
		mine = mine->next;
	if (ft_strcmp(mine->token, "echo") == 0
		&& ft_strncmp(mine->next->token, "-", 1) != 0)
		token->type = "argument";
	else
		token->type = "space";
}

void	grep_type(t_token *token, int index, int is_command)
{
	if ((token->prev && ft_strcmp(token->prev->token, ">") == 0)
		|| (token->prev && ft_strcmp(token->prev->token, ">>") == 0))
		token->type = "out";
	else if ((token->prev && ft_strcmp(token->prev->token, "<") == 0)
		|| (token->prev && ft_strcmp(token->prev->token, "<<") == 0))
		token->type = "in";
	else if (ft_strcmp(token->token, " ") == 0)
		grep_type_space(token);
	else if (ft_strcmp(token->token, "<<") == 0
		|| ft_strcmp(token->token, "<") == 0
		|| ft_strcmp(token->token, ">") == 0
		|| ft_strcmp(token->token, ">>") == 0
		|| ft_strcmp(token->token, "$") == 0)
		token->type = "operator";
	else if (index == 0 || is_command)
		token->type = "command";
	else if (ft_strcmp(token->token, "|") == 0)
		token->type = "pipe";
	else
		token->type = "argument";
}

static int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

char	*double_quotes(char *token)
{
	t_token_process	tp;
	char			start_quote;

	if (!token)
		return (NULL);
	tp.new_token = malloc((ft_strlen(token) + 1) * sizeof(char));
	if (!tp.new_token)
		return (NULL);
	tp.token = token;
	tp.i = 0;
	tp.pos = 0;
	start_quote = '\0';
	if (is_quote(token[0]))
		start_quote = token[tp.i++];
	while (token[tp.i])
	{
		if (token[tp.i] == start_quote && token[tp.i + 1] == '\0')
			break ;
		tp.new_token[tp.pos++] = token[tp.i++];
	}
	tp.new_token[tp.pos] = '\0';
	return (tp.new_token);
}