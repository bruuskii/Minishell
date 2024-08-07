#include "../minishell.h"



int count_char(char *cmd, char c)
{
    int count;

    if (!cmd || !c)
        return (0);
    count = 0;
    while (*cmd)
    {
        if (*cmd == c)
            count++;
        cmd++;
    }
    return (count);

}


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
        
        if (!ft_strncmp(cmd[i], "-n", 2) && i == 1)
        {
            if (count_char(cmd[i], '-') > 1)
                printf("%s", cmd[i]);
            else
                iswith_nl = 0;
        }  
        else
            printf("%s", cmd[i]);
        
        i++;
    }
    if (iswith_nl)
    {
        printf("\n");
    }
        
}