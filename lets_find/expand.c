#include "minishell.h"

void expand(t_token *token, t_env *env, char **str, int index) {
    if (token && strcmp(token->type, "expand") == 0) {
        free(token);
        t_token *next_token = malloc(sizeof(t_token));
        //strcpy(next_token->token, str[index + 1]);
        next_token->token = str[index + 1];
        next_token->type = "argument";

        if (!next_token) return;

        char dest[100];
        int i = 0;

        int len = strlen(next_token->token);
        while (env) {
            if (strncmp(env->line, next_token->token, len) == 0 && env->line[len] == '=') {
                const char *value = env->line + len + 1;
                while (*value) {
                    dest[i++] = *value++;
                }
                dest[i] = '\0';
                break;
            }
            env = env->next;
        }

        if (i > 0) {
            free(next_token->token);
            next_token->token = strdup(dest);
        }

        // Print the expanded token
        //printf(" expand: %s\n", next_token->token);
    }
    return ;
}

