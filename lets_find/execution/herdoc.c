#include "../minishell.h"



void handle_sig_herdoc(int sig)
{
    if (sig == SIGINT)
    {
        exit(2);
    }
}



// int ft_heredoc(char *delimeter, int fd)
// {
//     int pipe_fd[2];
//     char *tmp = "\0";

//     if (pipe(pipe_fd) == -1)
//     {
//         ft_putstr_fd("error pipe\n", 2);
//         exit(-1);
//         return (-1);
//     }
    
//     while (1)
//     {   

//         // signal(SIGQUIT, SIG_IGN);
//         // signal(SIGINT, handle_sig_herdoc);

//         printf("i'm in while\n");

//         tmp = readline("> ");
//         if (tmp == NULL)
//         {
//             ft_putstr_fd("bash: warning: here-document\n", 2);
//             exit(-1);
//             return (-1);
//         }
//         if (ft_strcmp(tmp, delimeter) == 0)
//             break;
//         if (write(pipe_fd[1], tmp, ft_strlen(tmp)) == -1)
//         {
//             ft_putstr_fd("write error\n", 2);
//             close (pipe_fd[0]);
//             close (pipe_fd[1]);
//             free(tmp);
//             exit(-1);
//             return (-1);
//         }
//         if (write(pipe_fd[1], "\n", 1) == -1)
//         {
//             ft_putstr_fd("write error\n", 2);
//             close (pipe_fd[0]);
//             close (pipe_fd[1]);
//             free(tmp);
//             exit(-1);
//             return (-1);
//         }
//     }
//     close(pipe_fd[1]);
//     free(tmp);

//     printf("pipe in fd 0 :%d:\n", pipe_fd[0]);
//     exit(pipe_fd[0]);
    
//     return (pipe_fd[0]);
// }

int ft_heredoc(char *delimeter, int fd)
{
    int pipe_fd[2];
    char *tmp = "\0";

    if (pipe(pipe_fd) == -1)
    {
        ft_putstr_fd("error pipe\n", 2);
        exit(1);
        return (-1);
    }
    
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