#include "../minishell.h"

void pwd()
{
    char    *cwd;

     cwd = getcwd(NULL, 0);
     if (!cwd)
     {
          ft_putstr_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n",
                     STDOUT_FILENO);
          g_exec->exit_status = 1;
     }
     else
     {
          ft_putendl_fd(cwd, STDOUT_FILENO);
          g_exec->exit_status = 0;
     }
     if (cwd)
          free (cwd);
}