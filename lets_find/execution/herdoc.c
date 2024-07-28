#include "../minishell.h"



// void handle_sig_herdoc(int sig)
// {
//     if (sig == SIGINT)
//     {
//         write(1, "\n", 1);
//         exit(99);
//          free()all all;
//     }
// }



//    if i have a lot of just append files;
int heredoc(char *delimeter)
{
    int pipe_fd[2];
    char *tmp;

    if (pipe(pipe_fd) == -1)
    {
        printf("error pipe");
        exit(-5);//  handle les ressources;
    }

    // signal(SIGQUIT, SIG_IGN);
    // signal(SIGINT, handle_sig_herdoc);
    while (1)
    {
        tmp = readline("> ");
        if (tmp == NULL)
        {
            printf("tmp = NULL\n");
            exit(-5);
        }
        if (ft_strncmp(tmp, delimeter, ft_strlen(delimeter)) == 0)
            break;
        if (write(pipe_fd[1], tmp, ft_strlen(tmp)) == -1)
        {
            printf("Error");
            free(tmp);// close pipes;
            exit(-5);
        }
        if (write(pipe_fd[1], "\n", 1) == -1)
        {
            printf("Error");
            free(tmp);// close pipes;
            exit(-5);
        }
    }
    close(pipe_fd[1]);
    free(tmp);
    return (pipe_fd[0]);
}
