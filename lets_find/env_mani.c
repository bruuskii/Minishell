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

