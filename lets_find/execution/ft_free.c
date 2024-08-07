#include "../minishell.h"






/*
    exec -> 
    t_token *tokens;
    t_cmd *cmd;
    char **Paths;
    t_env *env;
    int exit_status;


    token ->
    char *token;
    char *type;
    int nbr_of_args;
    struct s_token *next;
    struct s_token *prev;


    cmd ->
    char **cmd;
    struct s_filedescriptiom *infile;
    struct s_filedescriptiom *outfile;
    struct s_cmd *next;
    int *fd;

    filedescription ->
    char    *filename;
    int     isherdoc;
    int     iswithappend;
    char    *delimeter;
    struct s_filedescriptiom *next;

    env ->
    char *line;
    struct s_env *next;
    struct s_env *prev;

*/

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

void	free_db_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
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
    if (NodeToDelete->cmd)
        free_db_arr(NodeToDelete->cmd);
    if (NodeToDelete->fd)
        free (NodeToDelete->fd);
    // free in out files;
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
    
    // if not exit
    // free_tokens();
    // free_cmd();
    // free_dpchar_arr();
    // free filedescription;
    if (isexit)
    {
        // free all with : 
        // free_env();
    }

    
    
}