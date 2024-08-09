#include "../minishell.h"




int is_number_valid(char *nb)
{
    int i;
    int nbsign;
    int isdigitfound;

    i = 0;
    nbsign = 0; 
    while (nb[i])
    {
        if (!(ft_isdigit(nb[i]) || nb[i] == '+' 
            || nb[i] == '-' ||is_blanks(nb[i])))
            return (2);
        if (nb[i] == '-' || nb[i] == '+')
            nbsign++;
        if (ft_isdigit(nb[i]))
            isdigitfound = 1;
        i++;
    }
    if (nbsign > 1)
        return (2);
    return (1);
}

void    ft_exit(char **cmd)
{
    int i;
    int status;

    status = 0;
    if (!cmd[1])
    {
        //free ALL things;
        exit(0);
    }
    i = -1;
    while (cmd[++i])
    {
        status = is_number_valid(cmd[i]);
        if (status == 2)
        {
            ft_putstr_fd("exit numeric argument required\n", 2);
            //free all;
            exit (2);
        }
        // i++;
    }

    if (i > 1)
        ft_putstr_fd("exit: too many arguments\n", 2);
    else
    {
        exit (ft_atoi(cmd[1]));
        // free all things;
    }
}