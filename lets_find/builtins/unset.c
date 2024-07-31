#include "../minishell.h"





// int getequalindex(char *cmd)
// {
//     int i;

//     i = 0;
//     while (cmd[i])
//     {
//         if (cmd[i] == '=')
//         {
//             if (cmd[i - 1] == '+')
//                 return (i - 1);
//             return (i);
//         }
//         i++;
//     }
//     return (-1);
// }







t_env *check_in_env(t_env *env, char *word)
{
    int   indexofequal = 0;
    char *word_to_check;

    while (env)
    {
        
        if (env)
            indexofequal = getequalindex(env->line);
        if (indexofequal != -1)
        {
            word_to_check = malloc (indexofequal + 1);
            ft_strlcpy(word_to_check, env->line, indexofequal + 1);
            if (!ft_strncmp(word_to_check, word, ft_strlen(word_to_check)))
                return (env);
        }   
        else if (!ft_strncmp(env->line, word, ft_strlen(env->line)))
        {
            return (env);
        }
        env = env->next;
    }
    return (NULL);
}



void unset(char **cmd)
{
    t_env *env;
    t_env *env_x;
    int i;

    if (!cmd[1])
        return;
    i = 1;
    while (cmd[i])
    {
        env = check_in_env(g_exec->env, cmd[i]);
        env_x = check_in_env(g_exec->env_export, cmd[i]);

        if (env)
            DeleteNode(&g_exec->env, env);
        if (env_x)
            DeleteNode(&g_exec->env_export, env_x);
        i++;
    }
}