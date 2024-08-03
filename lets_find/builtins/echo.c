#include "../minishell.h"





void echo(char **cmd)
{
    int i;
    int iswith_nl;

    if (!cmd[1])
    {
        write(1, "\n", 1);
        return;
    }
    i = 1;
    iswith_nl = 1;
    while (cmd[i])
    {
        if (i == 1  && !ft_strncmp("-n", cmd[i], ft_strlen(cmd[i])))
        {
            iswith_nl = 0;
        }
        if (cmd[i] && !ft_strncmp("-n", cmd[i], 2))
            write(1, cmd[i], ft_strlen(cmd[i]));
        i++;
    }
    if (iswith_nl)
        write(1, "\n", 1);
}