#include"../minishell.h"

int cd_builtin(const char *path, t_env *env)
{
    if (path == NULL)
    {
        const char *home = getenv("HOME");
        if(home == NULL)
        {
            printf("cd: HOME environment variable not set\n");
            return 0;
        }
        path = home;
    }
    if(chdir(path) == 0)
    {
        save_old_pwd(env);
        save_current_pwd(env);
    }
    else
    {
            printf("unvalid path\n");
    }
    return 1;
}
