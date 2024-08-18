
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
    t_env   *temp;
    char    *check_with;
    int     i;

    temp = env;
    i = 0;
    while (temp)
    {
        i = getequalindex(temp->line);
        check_with = malloc(i + 1);
        if (!check_with)
            return (NULL);
        ft_strlcpy(check_with, temp->line, i + 1);
        if (!strncmp(check_with, value_to_check, strlen(value_to_check) + 1))
        {
            free(check_with);
            return (temp);
        }
        free(check_with);
        temp = temp->next;
    }
    return (NULL);
}

char *remove_char_(char *str, char c)
{
    int i;
    char *s;
    int j;
    int isfirstplusfound;

    s = malloc(ft_strlen(str) + 1);
    if (!s || !str)
        return (NULL);
    i = 0;
    j = 0;
    isfirstplusfound = 0;
    while (str[i])
    {
        if (str[i] != c || isfirstplusfound)
        {
            s[j] = str[i];
            j++;
        }
        else
            isfirstplusfound = 1;
        i++;
    }
    if (str)
        free(str);
    return (s[j] = '\0', s);
}


void    update_in_env(t_env *temp, char *word_to_app, int isappend, char *cmd)
{
    if (isappend)
    {
        if (!ft_strchr(temp->line, '='))
            temp->line = ft_strjoin(temp->line, "=");
        temp->line = ft_strjoin(temp->line, word_to_app);
    }  
    else
    {
        if (ft_strchr(cmd, '='))
        {
            free(temp->line);
            temp->line = ft_strdup(cmd);
        }
    }
}

void    add_to_env(t_env *temp, int isappend, char *cmd)
{
    temp = (t_env *)  malloc (sizeof(t_env));
    if (isappend)
        temp->line = remove_char_(ft_strdup(cmd), '+');
    else
        temp->line = ft_strdup(cmd);
    temp->next = NULL;
    InsertAtEnd(&g_exec->env, temp);
}

void ft_export2(char *cmd, int indexofequal)
{
    char *value_to_check;
    t_env *temp;
    int isappend;
    char *word_to_app;

    value_to_check = malloc(indexofequal + 1);
    ft_strlcpy(value_to_check, cmd, indexofequal +1);
    temp = is_in_env(g_exec->env, value_to_check);
    word_to_app = NULL;
    isappend = 0;
    if (cmd[indexofequal] == '+')
    {
        isappend = 1;
        word_to_app = ft_strdup(&cmd[indexofequal + 2]);
    }
    if (temp)
        update_in_env(temp, word_to_app, isappend, cmd);
    else
        add_to_env(temp, isappend, cmd);
    if (word_to_app)
        free (word_to_app);
    if (value_to_check)
        free (value_to_check);
    // update_env_arr();
}

int getequalindex(char *cmd)
{
    int i;

    i = 0;
    if (!cmd)
        return (0);
    while (cmd[i])
    {
        if (cmd[i] == '+' || cmd[i] == '=')
            break;
        i++;
    }
    return (i);
}

void ft_export(char *cmd)
{
    ft_export2(cmd, getequalindex(cmd));
}


int check_syntax(char *cmd)
{
    int i;
    int equalfound;

    i = 0;
    equalfound = 0;
    if (ft_isspace(cmd[i]) || ft_isdigit(cmd[i]) || !strncmp(cmd, "=", strlen(cmd)))
        return (0);
    while (cmd[i])
    {
        if (!(ft_isalnum(cmd[i]) || cmd[i] == '_' || cmd[i] == '+' || cmd[i] == '=' || cmd[i] == '$') 
            && !equalfound)
            return (0);
        if (cmd[i] == '+' && (cmd[i + 1] == '\0' || cmd [i + 1] != '=') && !equalfound)
            return (0);
        if (cmd[i] == '=')
        {
            equalfound = 1;
            if (ft_isspace(cmd[i + 1]))
                return (0);
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
        print_env(g_exec->env, 1);
        return;
    }
    while (cmd[i])
    {
        if (check_syntax(cmd[i]))
        {
            ft_export(cmd[i]);
        }
        else
        {
            printf("%s not a valid identifier\n", cmd[i]);
            g_exec->exit_status = 1;
        }
        i++;
    }
}