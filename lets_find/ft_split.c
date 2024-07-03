#include "minishell.h"

const char *operations[] = {"<<", "<", ">>", ">", "|", "$", " "};
int num_operations = sizeof(operations) / sizeof(operations[0]);

int is_operator(const char *str) {
    int op_len;

    for (int k = 0; k < num_operations; k++) {
        op_len = strlen(operations[k]);
        if (strncmp(str, operations[k], op_len) == 0) {
            return op_len;
        }
    }
    return 0;
}

char **split_string(const char *str) {
    int i = 0, count = 0;
    int len = strlen(str);
    
    // First pass to count tokens
    while (i < len) {
        //printf("%d\n", i);
        while (i < len && isspace(str[i])) {
            i++;
        }

        if (i >= len) break;

        if ((str[i] == '"' && i>0 && str[i- 1] == ' ') || (str[i] == '\'' && i>0 && str[i- 1] == ' ')) {
            char quote = str[i];
            i++;
            while (i < len && str[i] != quote) {
                i++;
            }
            if (i < len) i++; // Move past the closing quote
            count++;
        } else {
            //printf("ff");
            int op_len = is_operator(&str[i]);
            if (op_len > 0) {
                count++;
                i += op_len;
            } else {
                while (i < len && !isspace(str[i]) && !is_operator(&str[i]) && str[i] != '"' && str[i] != '\'') {
                    i++;
                }
                count++;
            }
            i++;
        }
    }

    char **result = (char **)malloc((count + 1) * sizeof(char *));
    i = 0;
    int index = 0;

    // Second pass to extract tokens
    while (i < len) {
        while (i < len && isspace(str[i])) {
            i++;
        }

        if (i >= len) break;

        if ((str[i] == '"' && i>0 && str[i- 1] == ' ')  || (str[i] == '\'' && i>0 && str[i- 1] == ' ')) {
            char quote = str[i];
            int start = i;
            i++;
            while (i < len && str[i] != quote) {
                i++;
            }
            if (i < len) i++; // Move past the closing quote
            int token_len = i - start;
            result[index] = (char *)malloc((token_len + 1) * sizeof(char));
            strncpy(result[index], &str[start], token_len);
            result[index][token_len] = '\0';
        } else {
            int start = i;
            int op_len = is_operator(&str[i]);
            if (op_len > 0) {
                result[index] = (char *)malloc((op_len + 1) * sizeof(char));
                strncpy(result[index], &str[i], op_len);
                result[index][op_len] = '\0';
                i += op_len;
            } else {
                while (i < len && !isspace(str[i]) && !is_operator(&str[i]) && str[i] != '"' && str[i] != '\'') {
                    i++;
                }
                int token_len = i - start;
                result[index] = (char *)malloc((token_len + 1) * sizeof(char));
                strncpy(result[index], &str[start], token_len);
                result[index][token_len] = '\0';
            }
            i++;
        }
        index++;

        while (i < len && isspace(str[i])) {
            i++;
        }
    }

    result[index] = NULL;
    return result;
}

void split_one_time(char *str)
{
    int len = strlen(str);
    int i = 0;
    int count = 0;
    while(i < len)
    {
        if(str[i] == ' ')
        {
            count++;
        }
        i++;
    }
    char **one_result = (char **)malloc((count + 1) * sizeof(char *));
    i = 0;
    count = 0;
    while(str[i] != ' ' || !is_operator(&str[i]))
    {
        count++;
        i++;
    }
    one_result[0] = (char *)malloc((count + 1) * sizeof (char));
    i = 0;
    while(i < count)
    {
        one_result[0][i] = str[i];
        i++;
    }
}