/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 21:58:11 by izouine           #+#    #+#             */
/*   Updated: 2024/08/20 14:24:20 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./Libft/libft.h"

static char	*handle_exit_status(char *final)
{
	char	*exit_status_str;
	char	*temp;
	size_t	final_len;
	size_t	exit_status_len;

	exit_status_str = ft_itoa(g_exec->exit_status);
	if (!exit_status_str)
	{
		free(final);
		return (NULL);
	}
	final_len = ft_strlen(final);
	exit_status_len = ft_strlen(exit_status_str);
	temp = (char *)malloc(final_len + exit_status_len + 1);
	if (!temp)
	{
		free(exit_status_str);
		free(final);
		return (NULL);
	}
	ft_strlcpy(temp, final, final_len + 1);
	ft_strlcat(temp, exit_status_str, final_len + exit_status_len + 1);
	free(exit_status_str);
	free(final);
	return (temp);
}

static char	*copy_env_value(char *final, const char *path)
{
	char	strr[100];
	size_t	j;
	char	*temp;

	ft_memset(strr, 0, sizeof(strr));
	j = 0;
	while (path[j] != '\0' && j < sizeof(strr) - 1)
	{
		strr[j] = path[j];
		j++;
	}
	strr[j] = '\0';
	temp = (char *)malloc(ft_strlen(final) + ft_strlen(strr) + 1);
	if (!temp)
	{
		free(final);
		return (NULL);
	}
	ft_strlcpy(temp, final, ft_strlen(final) + 1);
	ft_strlcat(temp, strr, ft_strlen(final) + ft_strlen(strr) + 1);
	free(final);
	return (temp);
}

static char	*handle_env_variable(char *final, char *dest, t_env *env)
{
	size_t		len;
	const char	*path;

	len = ft_strlen(dest);
	while (env)
	{
		if (ft_strncmp(env->line, dest, len) == 0 && env->line[len] == '=')
		{
			path = env->line + len + 1;
			return (copy_env_value(final, path));
		}
		env = env->next;
	}
	return (final);
}

static char	*append_char(char *final, char c)
{
	char	*temp;
	size_t	len;

	len = ft_strlen(final);
	temp = (char *)malloc(len + 2);
	if (!temp)
	{
		free(final);
		return (NULL);
	}
	ft_strlcpy(temp, final, len + 1);
	temp[len] = c;
	temp[len + 1] = '\0';
	free(final);
	return (temp);
}

static char	*handle_dollar_sign(char *final, t_token *token, t_env *env, int *i)
{
	char	dest[100];
	int		j;

	(*i)++;
	if (token->token[*i] == '?')
	{
		final = handle_exit_status(final);
		(*i)++;
	}
	else
	{
		j = 0;
		ft_memset(dest, 0, sizeof(dest));
		while (token->token[*i] != '$' && token->token[*i] != '\0'
			&& token->token[*i] != ' ' && token->token[*i] != '\''
			&& token->token[*i] != '"' && token->token[*i] != '?'
			&& j < (int) sizeof(dest) - 1)
		{
			dest[j++] = token->token[(*i)++];
		}
		(*i)--;
		final = handle_env_variable(final, dest, env);
	}
	return (final);
}

static void	update_quote_status(char c, int *in_s_quote, int *in_d_quote)
{
	if (c == '\'' && !(*in_d_quote))
		*in_s_quote = !(*in_s_quote);
	else if (c == '"' && !(*in_s_quote))
		*in_d_quote = !(*in_d_quote);
}

static char	*process_char(char *final, t_token *token, t_env *env, int *i)
{
	if (token->token[*i] == '$' && token->token[*i + 1] != '\0')
		final = handle_dollar_sign(final, token, env, i);
	else
		final = append_char(final, token->token[*i]);
	return (final);
}

static char	*process_token(t_token *token, t_env *env)
{
	char	*final;
	int		i;
	int		in_s_quote;
	int		in_d_quote;

	final = ft_strdup("");
	if (!final)
		return (NULL);
	i = 0;
	in_s_quote = 0;
	in_d_quote = 0;
	while (token->token[i])
	{
		update_quote_status(token->token[i], &in_s_quote, &in_d_quote);
		if (!in_s_quote)
			final = process_char(final, token, env, &i);
		else
			final = append_char(final, token->token[i]);
		if (!final)
			return (NULL);
		i++;
	}
	return (final);
}

int	expand(t_token *token, t_env *env, char **str, int index)
{
	char	*final;

	(void)index;
	(void)str;
	final = process_token(token, env);
	if (!final)
		return (-1);
	free(token->token);
	token->token = ft_strdup(final);
	free(final);
	return (1);
}
