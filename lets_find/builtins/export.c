
#include "../minishell.h"




void    InsertAtEnd(t_env **head, t_env *node_to_add)
{
    t_env *Temp;
   
    Temp = NULL;
    if (!(*head))
    {
        (*head) = node_to_add;
        return;
    }
    Temp = (*head);
    while (Temp->next != NULL)
        Temp = Temp->next;
    Temp->next = node_to_add;
    node_to_add->prev = Temp;
    node_to_add->next = NULL;
}

t_env *is_in_env(t_env *env, char *value_to_check)
{
    t_env *temp;

    temp = env;
    while (temp)
    {
        if (!strncmp(temp->line, value_to_check, strlen(value_to_check) + 1))
        {
            return (temp);
        }
        temp = temp->next;
    }
    return (NULL);
}

void DeleteNode(t_env **head, t_env *NodeToDelete)
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



char *remove_char_(char *str, char c)
{
    int i;
    char *s;
    int j;

    s = malloc(ft_strlen(str) + 1);
    if (!s)
        return (NULL);
    i = 0;
    j = 0;
    if (!str)
        return (NULL);

    while (str[i])
    {
        if (str[i] != c)
        {
            s[j] = str[i];
            j++;
        }
        i++;
    }
    s[j] = '\0';
    if (str)
        free(str);
    return (s);
}


void ft_export2(char *cmd, int indexofequal)
{
    char *value_to_check;
    t_env *envAdd;
    t_env *temp;
    t_env *temp2;

    value_to_check = malloc(indexofequal + 1);
    ft_strlcpy(value_to_check, cmd, indexofequal +1);
    temp = is_in_env(g_exec->env, value_to_check);
    temp2 = is_in_env(g_exec->env_export, value_to_check);

    int isappend = 0;
    char *word_to_app;

    if (cmd[indexofequal] == '+')
    {
        isappend = 1;
        word_to_app = ft_strdup(&cmd[indexofequal + 2]);
    }

    if (temp)
    {
        if (isappend)
            temp->line = ft_strjoin(temp->line, word_to_app);
        else
        {
            free(temp->line);
            temp->line = ft_strdup(cmd);
        }
    }
    else
    {
        envAdd = (t_env *)  malloc (sizeof(t_env));
        envAdd->line = remove_char_(ft_strdup(cmd), '+');
        envAdd->next = NULL;
        InsertAtEnd(&g_exec->env, envAdd);
    }
    if (temp2)
        DeleteNode(&g_exec->env_export, temp2);
}

int getequalindex(char *cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '=')
        {
            if (cmd[i - 1] == '+')
                return (i - 1);
            return (i);
        }
        i++;
    }
    return (-1);
}

void ft_export3(char *cmd)
{
    int indexofequal;
    t_env *temp;
    t_env *envAdd;
    t_env  *tmp;

    indexofequal = getequalindex(cmd);
    if (indexofequal == -1)
    {
            temp = is_in_env(g_exec->env_export, cmd);
            tmp = is_in_env(g_exec->env, cmd);
            if (tmp)
                printf("yes :%s:\n", tmp->line);
            if (!temp && !tmp)
            {
                envAdd = (t_env *)malloc(sizeof(t_env));
                envAdd->line = ft_strdup(cmd);
                envAdd->next = NULL;
                printf("line to add:%s:\n", envAdd->line);
                InsertAtEnd(&g_exec->env_export, envAdd);
            }
    }
    else
    {  
        ft_export2(cmd, indexofequal);
    }
}




int has_value(char *cmd)
{
    int i = 0;

    while (cmd[i])
    {
        if (cmd[i]== '=' && cmd[i + 1] != '\0')
        {
            return (1);
        }
        i++;
    }
    return (0);
}

int emptyvalue(char *cmd)
{
    int i = 0;

    while (cmd[i])
    {
        if (cmd[i]== '=' && cmd[i + 1] != '\0')
        {
            return (1);
        }
        i++;
    }
    return (0);
}


int check_syntax(char *cmd)
{
    int i = 0;
    int equalfound = 0;

    if (isspace(cmd[i]) || isdigit(cmd[i]))
    {
        printf("%s not a valid identifier\n", cmd);
        return (0);
    }
       
    if (!strncmp(cmd, "=", strlen(cmd)))
    {
        printf("%s not a valid identifier\n", cmd);
        return (0);
    }
    while (cmd[i])
    {
        if (!(isalnum(cmd[i]) || cmd[i] == '_' || cmd[i] == '+' || cmd[i] == '=' || cmd[i] == '$') 
            && !equalfound)
        {   
            printf("%s not a valid identifier\n", cmd);
            return (0);
        }
        if (cmd[i] == '+' && (cmd[i + 1] == '\0' || cmd [i + 1] != '='))
        {
            printf("%s not a valid identifier\n", cmd);
            return (0);
        }
        if (cmd[i] == '=')
        {
            equalfound = 1;
            if (isspace(cmd[i + 1]))
            {
                printf("%s not a valid identifier\n", cmd);
                return (0);   
            }
        } 
        i++;
    }
    return (1); 
}



void    print_env_export(t_env *env_export)
{
    t_env *temp;

    temp = env_export;
    while (temp)
    {
        printf("declare -x %s\n", temp->line);
        temp = temp->next;
    }
}

void export(char **cmd)
{
    int i = 1;

    if (!cmd[1])
    {
        print_env_export(g_exec->env_export);
        return;
    }
    while (cmd[i])
    {
        if (check_syntax(cmd[i]))
        {
            ft_export3(cmd[i]);
        }
        i++;
    }
}