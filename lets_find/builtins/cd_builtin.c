#include"../minishell.h"

// int cd_builtin(const char *path, t_env *env)
// {
//     t_env *env_tmp;

//     if (path == NULL)
//     {
//         env_tmp = is_in_env(g_exec->env, "HOME");
//         if(env_tmp == NULL)
//         {
//             //ft_putstr_fd("cd: variable not set\n", 2);
//             return 0;
//         }
//         path = env_tmp->line;
//     }
//     printf("path:%s:\n", path);
//     if(chdir(path) != 0)
//     {
//         //ft_putstr_fd("unvalid path\n", 2);
//         g_exec->exit_status = 1;
//         return 0;
//     }
//     else
//     {
//         save_old_pwd(env);
//         save_current_pwd(env);
//     }
//     return 1;
// }



void    cd_home()
{
    t_env *tmpenv;
    int     value;

    tmpenv = is_in_env(g_exec->env, "HOME");
    if (!tmpenv)
    {
        ft_putstr_fd("faild to change directory\n", 2);
        g_exec->exit_status = 1;
    }
    else
    {   
        value = chdir(tmpenv->line + 5);
        if (value != 0)
        {
            ft_putstr_fd("cd faild to change directory", 2);
            g_exec->exit_status = 1;
        }
        else
        {
            g_exec->exit_status = 0;
            save_old_pwd(g_exec->env);
            save_current_pwd(g_exec->env);
        }
    }
}

void    cd_path(char *path)
{
    char    *cwd;
    int     value;

    value = chdir(path);
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        ft_putstr_fd("getcwd: cannot access parent directories: No such file or directory\n", 2);
        g_exec->exit_status = 1;
        return;
    }
    else if (value != 0)
    {
        ft_putstr_fd("chdir connot change directory\n", 2);
        g_exec->exit_status = 1;
        return;
    }
    else
    {
        g_exec->exit_status = 0;
        save_old_pwd(g_exec->env);
        save_current_pwd(g_exec->env);
    }
}

void cd_builtin(char **cmd)
{
    if (!cmd[1])
    {
        cd_home();
    }
    else
    {
        cd_path(cmd[1]);
    }
}

int cd (char **cmd)
{
    if (cmd[1] && cmd[2])
    {
        g_exec->exit_status = 1;
        ft_putstr_fd("cd to many arguments AKhey\n", 2);
        return 0;
    }
    cd_builtin (cmd);
    return (1);
}
