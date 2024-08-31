/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:39:49 by izouine           #+#    #+#             */
/*   Updated: 2024/08/31 12:06:50 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Libft/libft.h"
#include "minishell.h"

char	*handle_exit_status(char *final)
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

char	*copy_env_value(char *final, const char *path)
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

char	*handle_env_variable(char *final, char *dest, t_env *env)
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

char	*append_char(char *final, char c)
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

char	*handle_quoted_dollar(char *final, t_token *token, size_t *i)
{
	char	quote;

	quote = token->token[*i];
	final = append_char(final, '$');
	final = append_char(final, quote);
	(*i)++;
	while (token->token[*i] && token->token[*i] != quote)
	{
		final = append_char(final, token->token[*i]);
		(*i)++;
	}
	if (token->token[*i] == quote)
	{
		final = append_char(final, quote);
		(*i)++;
	}
	return (final);
}
