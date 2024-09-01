/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:54:46 by izouine           #+#    #+#             */
/*   Updated: 2024/09/01 14:58:41 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_environment(char **envp)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	clear_screen(envp);
	g_exec = initexec(envp);
	increment_shell_level(g_exec->env);
}

void	process_command_line(char *line)
{
	if (ft_strlen(line) > 0)
	{
		add_history(line);
		print_type(line, g_exec->env, &g_exec->tokens, &g_exec->cmd);
		execute(g_exec);
		free(line);
	}
}

int	main_loop(void)
{
	char	*line;

	while (1)
	{
		g_exec->herdoc_sig = 0;
		line = readline(prompt());
		if (!line)
		{
			free_exec(1);
			return (0);
		}
		process_command_line(line);
		free_exec(0);
	}
}
