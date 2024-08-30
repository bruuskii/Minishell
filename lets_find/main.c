/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:48:09 by ainouni           #+#    #+#             */
/*   Updated: 2024/08/30 20:53:16 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*g_exec = NULL;

void	manual_strcat(char *dest, const char *src)
{
	while (*dest)
	{
		dest++;
	}
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
}

char	*prompt(void)
{
	static char	prompt_str[100];

	prompt_str[0] = '\0';
	manual_strcat(prompt_str, RED);
	manual_strcat(prompt_str, "ilyas");
	manual_strcat(prompt_str, RESET);
	manual_strcat(prompt_str, "@");
	manual_strcat(prompt_str, BLUE);
	manual_strcat(prompt_str, "bruski");
	manual_strcat(prompt_str, RESET);
	manual_strcat(prompt_str, ":~$ ");
	return (prompt_str);
}

void	clear_screen(char **envp)
{
	pid_t	pid;
	char	*clear[2];

	clear[0] = "/usr/bin/clear";
	clear[1] = NULL;
	pid = fork();
	if (pid == 0)
	{
		execve("/usr/bin/clear", clear, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

void	handle_sigint(int test)
{
	char	*str;

	(void)test;
	printf("\n");
	str = prompt();
	printf("%s", str);
	g_exec->exit_status = 130;
	free_exec(0);
	fflush(stdout);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	clear_screen(envp);
	g_exec = initexec(envp);
	increment_shell_level(g_exec->env);
	(void)argc;
	(void)argv;
	while (1)
	{
		g_exec->herdoc_sig = 0;
		line = readline(prompt());
		if (!line)
			break ;
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			print_type(line, g_exec->env, &g_exec->tokens, &g_exec->cmd);
			free(line);
			execute(g_exec);
		}
		free_exec(0);
	}
	free_exec(1);
	return (0);
}
