#include "minishell.h"

t_env *init_env(char **str) {
    if (str == NULL || str[0] == NULL) {
        return NULL;
    }

    t_env *head = NULL;
    t_env *current = NULL;
    t_env *previous = NULL;
    int i = 0;

    while (str[i]) {
        current = (t_env *)malloc(sizeof(t_env));
        if (!current) {
            while (head) {
                t_env *tmp = head;
                head = head->next;
                free(tmp);
            }
            return NULL;
        }

        current->line = strdup(str[i]);
        current->next = NULL;
        current->prev = previous;

        if (head == NULL) {
            head = current;
        }

        if (previous != NULL) {
            previous->next = current;
        }

        previous = current;
        i++;
    }

    return head;
}

void    print_env(t_env *env)
{
    while (env)
    {
        printf("%s\n", env->line);
        env = env->next;
    }
}


// i added the increment shlvl function, 
// i will make sure to channge all the forbiden function (strlen...)
void increment_shell_level(t_env *env) {
    t_env *current = env;
    char *shlvl_prefix = "SHLVL=";
    size_t prefix_len = strlen(shlvl_prefix);
    int shlvl_value;

    while (current) {
        if (strncmp(current->line, shlvl_prefix, prefix_len) == 0) {
            shlvl_value = atoi(current->line + prefix_len);
            shlvl_value++;
            
            char new_shlvl[16];
            char *i = ft_itoa(shlvl_value);
            strcpy(new_shlvl, shlvl_prefix);
            strcat(new_shlvl, i);
            free(current->line);
            current->line = strdup(new_shlvl);
            return;
        }
        current = current->next;
    }

    t_env *new_node = (t_env *)malloc(sizeof(t_env));
    if (new_node) {
        new_node->line = strdup("SHLVL=1");
        new_node->next = env;
        new_node->prev = NULL;
        if (env) {
            env->prev = new_node;
        }
        env = new_node;
    }
}

void save_old_pwd(t_env *env)
{
    int index = 4;
    t_env *pwd = env;
    char oldpwd[100];
    int i = 0;
    while(pwd)
    {
        if(strncmp(pwd->line, "PWD=", 4) == 0)
        {
            while(pwd->line[index] != '\0')
            {
                oldpwd[i] = pwd->line[index];
                i++;
                index++; 
            }
            oldpwd[i] = '\0';
            break;
        }
        pwd = pwd->next;
    }
    while(env)
    {
        if(strncmp(env->line, "OLDPWD=", 7) == 0)
        {
            free(env->line);
            size_t nbr_maloc = 7 + strlen(oldpwd) + 1;
            char *line = malloc(nbr_maloc);
            strcpy(line, "OLDPWD=");
            strcat(line, oldpwd);
            env->line = strdup(line);
            free(line);
            return ;
        }
        env = env->next;
    }
}

void save_current_pwd(t_env *env)
{}