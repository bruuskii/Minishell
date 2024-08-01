
#include "minishell.h"

int expand(t_token *token, t_env *env, char **str, int index) {
    (void)index;
    (void)str;
    char dest[100];
    char strr[100];
    int j = 0;
    char *final = NULL;
    int i = 0;

    final = (char *)malloc(1);
    if (!final)
        return -1;
    final[0] = '\0';

    while (token->token[i]) {
        if (token->token[i] == '$') {
            i++;
            if( token && token->token[i] == '?')
            {
                final = ft_itoa(g_exec->exit_status);
                free(token->token);
                token->token = strdup(final);
                free(final);
                return 1;
            }
            j = 0;
            memset(dest, 0, sizeof(dest));
            while (token->token[i] != '$' && token->token[i] != '\0') {
                dest[j] = token->token[i];
                i++;
                j++;
            }
            i--;
            int len = strlen(dest);
            while (env) {
                if (strncmp(env->line, dest, len) == 0 && env->line[len] == '=') {
                    const char *path = env->line + len + 1;
                    memset(strr, 0, sizeof(strr));
                    j = 0;
                    while (path[j] != '\0') {
                        strr[j] = path[j];
                        j++;
                    }
                    char *temp = (char *)malloc(strlen(final) + strlen(strr) + 1);
                    if (!temp) {
                        free(final);
                        return -1;
                    }
                    strcpy(temp, final);
                    strcat(temp, strr);
                    free(final);
                    final = temp;
                    break;
                }
                env = env->next;
            }
        } else {
            char *temp = (char *)malloc(strlen(final) + 2);
            if (!temp) {
                free(final);
                return -1;
            }
            strcpy(temp, final);
            temp[strlen(final)] = token->token[i];
            temp[strlen(final) + 1] = '\0';
            free(final);
            final = temp;
        }
        i++;
    }
    free(token->token);
    token->token = strdup(final);
    free(final);

    return 1;
}