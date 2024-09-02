/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:44:03 by izouine           #+#    #+#             */
/*   Updated: 2024/09/01 14:57:20 by izouine          ###   ########.fr       */
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
	char	**clear;

	clear = (char *[]){"/usr/bin/clear", NULL};
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
	(void)argc;
	(void)argv;
	initialize_environment(envp);
	return (main_loop());
}
