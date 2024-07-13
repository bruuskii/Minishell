
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
}

t_env *is_in_env(t_env *env, char *value_to_check)
{
    t_env *temp;

    temp = env;
    while (temp)
    {
        if (!strncmp(temp->line, value_to_check, strlen(value_to_check)))
        {
            return (temp);
        }
        temp = temp->next;
    }
    return (NULL);
}


void Append_line(t_env *temp, t_env *temp2, int indexofequal, char *cmd)
{
    char *tmp;

    tmp = &temp->line[indexofequal + 1];
    free(temp->line);
    temp->line = malloc (strlen(cmd) + strlen(tmp));
    strcpy(temp->line, tmp);
    strcpy(temp->line + strlen(tmp), cmd);
    free(temp2->line);
    temp2->line = malloc (strlen(cmd) + strlen(tmp));
    strcpy(temp2->line, tmp);
    strcpy(temp2->line + strlen(tmp), cmd);
}


void ft_export2(t_env *env, t_env *export_list, char *cmd, int indexofequal)
{
    char *value_to_check;
    t_env *envAdd;
    t_env *temp;
    t_env *temp2;

    value_to_check = malloc(indexofequal + 1);
    strncpy(value_to_check, cmd, indexofequal);
    temp = is_in_env(env, value_to_check);
    temp2 = is_in_env(export_list, value_to_check);         
    if (temp)
    {
        if (cmd[indexofequal - 1] == '+')
            Append_line(env,export_list, indexofequal, cmd);
        else 
         {
            free(temp->line);
            temp->line = malloc (strlen(cmd));
            strcpy(temp->line, cmd);
            free(temp2->line);
            temp2->line = malloc (strlen(cmd));
            strcpy(temp2->line, cmd);}
        }
    else
    {
        envAdd = (t_env *)malloc(sizeof(t_env));
        envAdd->line = strdup(cmd);
        envAdd->next = NULL;
        InsertAtEnd(&env, envAdd);
        InsertAtEnd(&export_list, envAdd);
    }
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

static void ft_export3(t_env *env, t_env *export_list, char *cmd)
{
    int indexofequal;
    t_env *temp;
    t_env *envAdd;

    indexofequal = getequalindex(cmd);
    if (indexofequal == -1)
    {
            temp = is_in_env(export_list, cmd);
            if (!temp)
            {
                envAdd = (t_env *)malloc(sizeof(t_env));
                envAdd->line = strdup(cmd);
                envAdd->next = NULL;
                InsertAtEnd(&export_list, envAdd);
            }
    }
    else
    {  
        ft_export2(env, export_list, cmd, indexofequal);
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

    // if (!strncmp(cmd, "$", strlen(cmd)))
    // {
    //     printf(" %s  not a valid identifier\n", cmd);
    //         return (0);
    // }

    if (isspace(cmd[i]))
        return (0);

    if (!strncmp(cmd, "=", strlen(cmd)))
    {
        printf(" %s  not a valid identifier\n", cmd);
            return (0);
    }

    while (cmd[i])
    {
        if (!(isalpha(cmd[i]) || cmd[i] == '_')   && !equalfound)
        {   
            printf(" %s  not a valid identifier\n", cmd);
            return (0);
        }
        if (cmd[i] == '=')
            equalfound = 1;
        i++;
    }

    //expand $?;
    return (1);
    
}


void export(t_env *env, t_env *export_list, char **cmd)
{
    int i = 0;

    // if (!cmd[1])    //  cmd [0] gonna be export; 
    // {
    //     print_env(export_list);
    //     return;
    // }
    while (cmd[i])
    {
        if (check_syntax(cmd[i]))
        {
            
            ft_export3(env, export_list, cmd[i]);//printf("J'ai entree\n");
        }
        i++;
    }
    //has value;   
}