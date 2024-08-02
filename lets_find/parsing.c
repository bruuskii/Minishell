#include "minishell.h"

int parse_every_word(char **tokens)
{
    int i;
    int index;
    int count_single = 0;
    int count_double = 0;
    index = 0;

    while(tokens &&tokens[index] != NULL)
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

    // if(index > 0 && tokens[index - 1] && is_operator(tokens[index - 1]) != 0)
    // {
    //     printf("bash: syntax error near unexpected token `newline'\n");
    //     return 0;
    // }

    if(count_single % 2 != 0 || count_double % 2 != 0)
    {
        printf("bash: unclosed quotes\n");
        return 0;
    }
    return 1;
}

void free_tokens(t_token *head) {
    t_token *tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp->token);
        free(tmp);
    }
}

int print_type(char *str, t_env *env, t_token **token, t_cmd **cmd) {
    (void)env;
    //(void)token;
    if (!str) {
        printf("here");
        return 0;
    }
    if(*token)
    {
        free_tokens(*token);
        *token = NULL;
    }
    if(!first_parse(str))
        return 0;

    char **real_tokens = split_string(str);
    if (!parse_every_word(real_tokens)) {
        return 0;
    }

    char **tokens = double_quotes(real_tokens);
    int index = 0;
    int args_nbr = 0;
    int is_command = 1;
    t_token *head = NULL;
    t_token *current = NULL;


    while (tokens && tokens[index]) {
        t_token *new_token = (t_token *)malloc(sizeof(t_token));
        if (!new_token) {
            // Free previously allocated tokens and return 0
            t_token *tmp = head;
            while (tmp) {
                t_token *next = tmp->next;
                free(tmp->token);
                free(tmp);
                tmp = next;
            }
            return 0;
        }

        new_token->token = strdup(tokens[index]);
        new_token->next = NULL;
        new_token->prev = current;
        new_token->nbr_of_args = args_nbr;
        if (current) {
            current->next = new_token;
        } else {
            head = new_token;
        }

        current = new_token;
        grep_type(current, index, is_command);

        expand(current, env, tokens, index);

        if (strcmp(current->type, "pipe") != 0 && index != 0 && strcmp(current->type, "argument") == 0) {
            args_nbr++;
            current->nbr_of_args = args_nbr;
        }

        if (strcmp(current->type, "pipe") == 0) {
            is_command = 1;
            printf("the number of these arguments %d\n", current->nbr_of_args);
            args_nbr = 0;
        } else {
            is_command = 0;
        }

        printf("token: %s, and type: %s\n", current->token, current->type);
        index++;
    }

    if( index > 0 && tokens[index - 1])
        printf("number of ac %d\n", current->nbr_of_args);
    current = head;

    (*cmd) = parse_every_command(current);
    index = 0;
    while (tokens[index]) {
        if (strcmp(tokens[index], "cd") == 0) {
            if (tokens[index + 1]) {
                if (cd_builtin(tokens[index + 1], env) == 0) {
                    printf("cd: failed to change directory\n");
                }
                index++;
            } else {
                if (cd_builtin(NULL, env) == 0) {
                    printf("cd: failed to change directory\n");
                }
            }
        }
        index++;
    }

    index = 0;
    while (tokens[index]) {
        free(tokens[index]);
        index++;
    }
    free(tokens);

    index = 0;
    while (real_tokens[index]) {
        free(real_tokens[index]);
        index++;
    }
    free(real_tokens);
    
    (*token) = head;
    return 1;
}


void grep_type(t_token *token, int index, int is_command) {
    if (strcmp(token->token, "<<") == 0 || strcmp(token->token, "<") == 0 ||
               strcmp(token->token, ">") == 0 || strcmp(token->token, ">>") == 0) {
        token->type = "operator";
    } else if (token->prev && (strcmp(token->prev->token, ">" ) == 0|| strcmp(token->prev->token, ">>") == 0)) {
        token->type = "out";
    } else if (token->prev && (strcmp(token->prev->token, "<") == 0 || strcmp(token->prev->token, "<<") == 0)) {
        token->type = "in";
    }else if (index == 0 || is_command) {
        token->type = "command";
    } else if (strcmp(token->token, "|") == 0) {
        token->type = "pipe";
    }
    else if(strcmp(token->token,  "$") == 0)
        token->type = "expand";
     else
     {
        token->type = "argument";
     }
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


