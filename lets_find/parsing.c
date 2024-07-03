#include "minishell.h"

int print_type(char *str) {
    char **real_tokens = split_string(str);
    parse_every_word(real_tokens);
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
    while (tokens[index] != NULL) {
        free(tokens[index]);
        index++;
    }
    //free(tokens);
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
    i = 0;
    int k = 0;
    int index = 0;
    int pos = 0;
    while (tokens[i]) {
        int len = strlen(tokens[i]);
        k = 0;
        pos = 0;
        real_tokens[index] = (char *)malloc((len + 1) * sizeof(char));
        if ((tokens[i][0] == '"' && tokens[i][len - 1] == '"' && len > 1) || (tokens[i][0] == '\'' && tokens[i][len - 1] == '\'' && len > 1)) {
            k++;
            while (k < len - 1) {
                real_tokens[index][pos] = tokens[i][k];
                pos++;
                k++;
            }
        } else {
            while (tokens[i][k]) {
                real_tokens[index][pos] = tokens[i][k];
                k++;
                pos++;
            }
        }
        real_tokens[index][pos] = '\0';
        i++;
        index++;
    }
    real_tokens[index] = NULL;
    return real_tokens;
}


int parse_every_word(char **tokens)
{
    int i;
    int index;
    int count_single = 0;
    int count_double = 0;
    index = 0;
    i = 0;
    while(tokens[index] != NULL)
    {
        i = 0;
        //int len = strlen(tokens[index]);
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

    if(count_single % 2 != 0 || count_double % 2 != 0)
    {
        write(2, "what the fuck!!\n", 16);
        return 0;
    }
    return 1;
}