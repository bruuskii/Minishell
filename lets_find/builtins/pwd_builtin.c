#include "../minishell.h"

void pwd(t_env *env)
{

    char dest[100];
    int index = 4;
    int d = 0;
    while(env)
    {
        if(ft_strncmp(env->line, "PWD=", 4) == 0)
        {
            while(env->line[index])
            {
                dest[d] = env->line[index];
                d++;
                index++;
            }
            dest[d] = '\0';
            printf("%s\n", dest);
        }
        env = env->next;
    }
}