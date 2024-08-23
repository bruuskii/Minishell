#include "../minishell.h"



void handle_sig_herdoc(int sig)
{
    if (sig == SIGINT)
    {
        exit(2);
        //2 for controle + c;
    }
}

int ft_heredoc(char *delimeter, int fd)
{
    char *tmp = "\0";
    
    while (1)
    {   

        signal(SIGQUIT, SIG_IGN);
        signal(SIGINT, handle_sig_herdoc);

        tmp = readline("");
        if (tmp == NULL)
        {
            ft_putstr_fd("bash: warning: here-document\n", 2);
            exit(0);
        }
        if (ft_strcmp(tmp, delimeter) == 0)
            break;
        if (write(fd, tmp, ft_strlen(tmp)) == -1)
        {
            ft_putstr_fd("write error\n", 2);
            free(tmp);
            exit(1);
        }
        if (write(fd, "\n", 1) == -1)
        {
            ft_putstr_fd("write error\n", 2);
            free(tmp);
            exit(1);
        }
    }
    free(tmp);
    exit(0);
    return (1);
}


int heredoc(char *delimeter, int fd)
{
    return (ft_heredoc(delimeter, fd));
}