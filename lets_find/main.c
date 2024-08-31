#include "minishell.h"

t_exec	*g_exec = NULL;

void	manual_strcpy(char *dest, const char *src)
{
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
}

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
	char	*clear[] = {"/usr/bin/clear", NULL};

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

void	ls_screen(char **envp)
{
	pid_t	pid;
	char	*clear[] = {"/usr/bin/ls", NULL};

	pid = fork();
	if (pid == 0)
	{
		execve("/usr/bin/ls", clear, envp);
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

void	exit_screen(char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execvp("exit", envp);
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

	// struct sigaction	sa;
	// sa.sa_handler = &handle_sigint;
	// sa.sa_flags = SA_RESTART; // For Ctr C
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
		{
			free_exec(1);
			break ;
		}
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			print_type(line, g_exec->env, &g_exec->tokens, &g_exec->cmd);
			execute(g_exec);
			free (line);
		}
		free_exec(0);
	}
	return (0);
}
