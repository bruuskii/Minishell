#include "../minishell.h"




int is_number_valid(char *nb)
{
    int i;
    int nbsign;

    i = 0;
    nbsign = 0;
    while (nb[i])
    {
        if (!(ft_isdigit(nb[i]) || nb[i] == '+' 
            || nb[i] == '-' ||is_blanks(nb[i])))
            return (2);
        if (nb[i] == '-' || nb[i] == '+')
            nbsign++;
        i++;
    }
    if (nbsign > 1)
        return (2);
    return (1);
}


void ft_exit1(char **cmd)
{
    int i;
    int status;

    i = 1;
    status = 0;
    while (cmd[i])
    {
        status = is_number_valid(cmd[i]);
        if (status == 2)
        {
            ft_putstr_fd("numeric argument required\n", 2);
            // free all;
            exit(2);
        }
    }
    
}

void    ft_exit(char **cmd)
{
    
    if (!cmd[1])
    {
        //free ALL things;
        exit(0);
    }
    ft_exit1(cmd);
}