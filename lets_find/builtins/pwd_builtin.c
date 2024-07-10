#include "../minishell.h"

void pwd(char **envp)
{
    t_env *env = init_env(envp);

    char dest[100];
    int index = 4;
    int d = 0;
    while(env)
    {
        if(strncmp(env->line, "PWD=", 4) == 0)
        {
            while(env->line[index])
            {
                dest[d] = env->line[index];
                d++;
                index++;
            }
            printf("%s\n", dest);
        }
        env = env->next;
    }
}