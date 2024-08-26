#include "../minishell.h"


void Delete_env_Node(t_env **head, t_env *NodeToDelete)
{
    if ((*head) == NULL || NodeToDelete == NULL) {
        return;
    }
    if ((*head) == NodeToDelete) {
        (*head) = NodeToDelete->next;
        if ((*head) != NULL)
            (*head)->prev = NULL;
    }
    if (NodeToDelete->next != NULL) {
        NodeToDelete->next->prev = NodeToDelete->prev;
    }
    if (NodeToDelete->prev != NULL) {
        NodeToDelete->prev->next = NodeToDelete->next;
    }

    if (NodeToDelete->line)
        free(NodeToDelete->line);
    if (NodeToDelete)
        free(NodeToDelete);
}




void Delete_token_Node(t_token **head, t_token *NodeToDelete)
{
    if ((*head) == NULL || NodeToDelete == NULL) {
        return;
    }
    if ((*head) == NodeToDelete) {
        (*head) = NodeToDelete->next;
        if ((*head) != NULL)
            (*head)->prev = NULL;
    }
    if (NodeToDelete->next != NULL) {
        NodeToDelete->next->prev = NodeToDelete->prev;
    }
    if (NodeToDelete->prev != NULL) {
        NodeToDelete->prev->next = NodeToDelete->next;
    }

    if (NodeToDelete->token)
        free(NodeToDelete->token);
    if (NodeToDelete->type)
        free (NodeToDelete->type);
    if (NodeToDelete)
        free(NodeToDelete);
}



void Delete_cmd_Node(t_cmd **head, t_cmd *NodeToDelete)
{
    t_cmd *current;

    current = (*head);
    if ((*head) == NULL || NodeToDelete == NULL)
        return;
    if ((*head) == NodeToDelete)
        (*head) = NodeToDelete->next;
    else
    {
        while (current->next && current->next != NodeToDelete)
            current = current->next;
    }
    if (current->next)
        current->next = NodeToDelete->next;
    free_db_arr(NodeToDelete->cmd);
    if (NodeToDelete->fd)
        free (NodeToDelete->fd);
    Delete_fd_Nodes(&NodeToDelete->outfile);
    Delete_fd_Nodes(&NodeToDelete->infile);
    if (NodeToDelete)
        free (NodeToDelete);
}



void Delete_fd_Node(t_filedescriptiom **head, t_filedescriptiom *NodeToDelete)
{
    t_filedescriptiom *current;

    current = (*head);
    if ((*head) == NULL || NodeToDelete == NULL) {
        return;
    }
    if ((*head) == NodeToDelete)
        (*head) = NodeToDelete->next;
    else
    {
        while (current->next && current->next != NodeToDelete)
            current = current->next;
    }
    if (current->next)
        current->next = NodeToDelete->next;
    if (NodeToDelete->delimeter)
        free(NodeToDelete->delimeter);
    if (NodeToDelete->filename)
        free (NodeToDelete->filename);
    if (NodeToDelete)
        free (NodeToDelete);
}

void    free_exec(int isexit)
{    
    Delete_cmds_node();
    if (g_exec->paths)
        free_db_arr(g_exec->paths);
    if (isexit)
    {
        Delete_env();
        if (g_exec)
            free(g_exec);
        ft_putstr_fd("exit\n", STDOUT_FILENO);
    }
}