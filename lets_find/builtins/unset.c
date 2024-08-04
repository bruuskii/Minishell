#include "../minishell.h"



void unset(char **cmd)
{
    t_env *env;
    int i;

    if (!cmd[1])
        return;
    i = 1;
    while (cmd[i])
    {
        env = is_in_env(g_exec->env, cmd[i]);
        if (env)
            DeleteNode(&g_exec->env, env);
        i++;
    }
}