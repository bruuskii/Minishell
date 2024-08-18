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
            Delete_env_Node(&g_exec->env, env);
        i++;
    }
    printf("yeah here\n");
    // update_env_arr();
}