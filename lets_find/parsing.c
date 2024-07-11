#include "minishell.h"

int parse_every_word(char **tokens)
{
    int i;
    int index;
    int count_single = 0;
    int count_double = 0;
    index = 0;

    while(tokens[index] != NULL)
    {
        i = 0;
        while(tokens[index][i] != '\0')
        {
            if(tokens[index][i] == '\'')
                count_single++;
            else if(tokens[index][i] == '\"')
                count_double++;
            i++;
        }
        index++;
    }

    if(tokens[index - 1] && is_operator(tokens[index - 1]) != 0)
    {
        printf("bash: syntax error near unexpected token `newline'\n");
        return 0;
    }

    if(count_single % 2 != 0 || count_double % 2 != 0)
    {
        printf("bash: unclosed quotes\n");
        return 0;
    }
    return 1;
}

int print_type(char *str, t_env *env) {
    if(!str)
    {
        printf("here");
        return (0);
    }
    char **real_tokens = split_string(str);
    if(!parse_every_word(real_tokens))
        return (0);
    char **tokens = double_quotes(real_tokens);
    int index = 0;
    int last_operator = 0;

    while (tokens[index] != NULL) {
        t_token token;
        token.token = tokens[index];
        if (index == 0) {
            token.type = "command";
        } else if (last_operator) {
            token.type = "command";
            last_operator = 0;
        } else if (strcmp(tokens[index], "|") == 0) {
            token.type = "operator";
            last_operator = 1;
        } else if (is_operator(tokens[index])) {
            token.type = "operator";
        } else {
            token.type = "argument";
        }
        printf("Token: %s, Type: %s\n", token.token, token.type);
        index++;
    }
    index = 0;

    while (tokens[index]) {
        if (strcmp(tokens[index], "cd") == 0) {
            if (tokens[index + 1]) {
                if (cd_builtin(tokens[index + 1], env) == 0) {
                    printf("cd: failed to change directory\n");
                }
                index++;
            } else {
                if (cd_builtin((NULL), env) == 0) {
                    printf("cd: failed to change directory\n");
                }
            }
        }
        index++;
    }
    index = 0;
    while (tokens[index] != NULL) {
        free(tokens[index]);
        index++;
    }
    index = 0;
    while (real_tokens[index] != NULL) {
        free(real_tokens[index]);
        index++;
    }
    free(real_tokens);
    return 1;
}

char **double_quotes(char **tokens) {
    int i = 0;
    while (tokens[i]) {
        i++;
    }
    
    char **real_tokens = (char **)malloc((i + 1) * sizeof(char *));
    if(!real_tokens)
    {
        free(real_tokens);
        return 0;
    }
    i = 0;
    int index = 0;

    while (tokens[i]) {
        int len = strlen(tokens[i]);
        int k = 0, pos = 0;
        int in_quote = 0;
        char current_quote = '\0';

        real_tokens[index] = (char *)malloc((len + 1) * sizeof(char));
        if(!real_tokens || !real_tokens[index])
        {
            int j = 0;
            while(j < len)
            {
                free(real_tokens[j]);
                j++;
            }
            free(real_tokens);
            return NULL;
        }
        while (k < len) {
            if ((tokens[i][k] == '"' || tokens[i][k] == '\'') && !in_quote) {
                in_quote = 1;
                current_quote = tokens[i][k];
            } else if (tokens[i][k] == current_quote && in_quote) {
                in_quote = 0;
                current_quote = '\0';
            } else {
                real_tokens[index][pos] = tokens[i][k];
                pos++;
            }
            k++;
        }

        real_tokens[index][pos] = '\0';
        i++;
        index++;
    }
    real_tokens[index] = NULL;

    return real_tokens;
}


