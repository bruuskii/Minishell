#include "../minishell.h"

int ft_heredoc(char *delimeter, int fd, char *tmp)
{
    if (tmp == NULL)
    {
        ft_putstr_fd("bash: warning: here-document\n", 2);
        exit(3);
    }
    if (ft_strcmp(tmp, delimeter) == 0)
        return (0);
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
    return (1);
}