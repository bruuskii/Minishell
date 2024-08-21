#include "../minishell.h"



void handle_sig_herdoc(int sig)
{
    if (sig == SIGINT)
    {
        printf("controle + c pressed\n");
        // g_exec->exit_status = 130;
        g_exec->herdoc_sig = 1;
        printf("\n:%d:\n", g_exec->herdoc_sig);
    }
}



int heredoc(char *delimeter)
{
    int pipe_fd[2];
    char *tmp;

    if (pipe(pipe_fd) == -1)
    {
        ft_putstr_fd("error pipe\n", 2);
        return (-1);
    }
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, handle_sig_herdoc);
    while (1)
    {
        if (g_exec->herdoc_sig == 1)
            return (-1);
        
        tmp = readline("> ");
        if (tmp == NULL)
        {
            ft_putstr_fd("bash: warning: here-document\n", 2);
            return (-1);
        }
        if (ft_strcmp(tmp, delimeter) == 0)
            break;
        if (write(pipe_fd[1], tmp, ft_strlen(tmp)) == -1)
        {
            ft_putstr_fd("write error\n", 2);
            close (pipe_fd[0]);
            close (pipe_fd[1]);
            free(tmp);
            return (-1);
        }
        if (write(pipe_fd[1], "\n", 1) == -1)
        {
            ft_putstr_fd("write error\n", 2);
            close (pipe_fd[0]);
            close (pipe_fd[1]);
            free(tmp);
            return (-1);
        }
    }
    close(pipe_fd[1]);
    free(tmp);
    return (pipe_fd[0]);
}
