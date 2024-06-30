#include "minishell.h"

int print_type(char *str) {
    char **tokens = split_string(str);
    int index = 0;
    int last_operator = 0;

    while (tokens[index] != NULL) {
        t_token token;
        token.token = tokens[index];
        if (index == 0) {
            token.type = "command";
        }else if(last_operator)
        {
            token.type = "command";
            last_operator = 0;
        }
        else if (is_operator(tokens[index])) {
            token.type = "operator";
            last_operator = 1;
        } else {
            token.type = "argument";
        }
        printf("Token: %s, Type: %s\n", token.token, token.type);
        index++;
    }
    parse_every_word(tokens);
    // index = 0;
    // while (tokens[index] != NULL) {
    //     free(tokens[index]);
    //     index++;
    // }
    free(tokens);
    return 1;
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

    if(count_single % 2 != 0 || count_double != 0)
    {
        write(2, "what the fuck!!\n", 16);
        return 0;
    }
    return 1;
}