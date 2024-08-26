#include "../minishell.h"

void    Delete_env()
{
    t_env   *env;
    t_env   *tmp;

    env = g_exec->env; 
    while (env && env->next)
    {
        tmp = env;
        env = env->next;
        Delete_env_Node(&g_exec->env, tmp);
    }
}


void	free_db_arr(char **arr)
{
	int i;

    i = 0;
    if (arr != NULL)
    {
	    while (arr[i])
	    {
		    if (arr[i])
			    free(arr[i]);
		    i++;
	    }
    free(arr);
    }
}

void    Delete_cmds_node()
{
    t_cmd *tmp;
    t_cmd  *cmd;

    cmd = g_exec->cmd;
    while (cmd && cmd->next)
    {
        tmp = cmd;
        cmd = cmd->next;
        Delete_cmd_Node(&g_exec->cmd, tmp);
    }
}

void    Delete_tokens()
{
    t_token *token;
    t_token *tmp;

    token = g_exec->tokens;
    while (token && token->next)
    {
        tmp = token;
        token = token->next;
        Delete_token_Node(&g_exec->tokens, tmp);
    }
}

void Delete_fd_Nodes(t_filedescriptiom **src)
{
    t_filedescriptiom *tmp;
    t_filedescriptiom *fd;

    fd = (*src);
    while (fd && fd->next)
    {
        tmp = fd;
        fd = fd->next;
        Delete_fd_Node(src, tmp);
    }
}