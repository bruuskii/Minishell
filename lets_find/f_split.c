#include "minishell.h"

const char *operations[] = {"<<", "<", ">>", ">", "|", "\"\"", "\'"};
int num_operations = sizeof(operations) / sizeof(operations[0]);

int is_operator(const char *str) {
    for (int k = 0; k < num_operations; k++) {
        int op_len = strlen(operations[k]);
        if (strncmp(str, operations[k], op_len) == 0) {
            return op_len;
        }
    }
    return 0;
}

int count_tokens(const char *str) {
    int i = 0, count = 0;
    int len = strlen(str);

    while (i < len) {
        while (i < len && isspace(str[i])) {
            i++;
        }

        if (i >= len) break;

        if (str[i] == '"' || str[i] == '\'') {
            char quote = str[i];
            i++;
            while (i < len && str[i] != quote) {
                i++;
            }
            i++; 
            count++;
        } else {
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
        }

        while (i < len && isspace(str[i])) {
            i++;
        }
    }
    return count;
}

char **split_string(const char *str) {
    int token_count = count_tokens(str);
    char **result = (char **)malloc((token_count + 1) * sizeof(char *));
    if (!result) {
        return NULL; // Allocation failed
    }

    int i = 0, index = 0;
    int len = strlen(str);

    while (i < len) {
        while (i < len && isspace(str[i])) {
            i++;
        }

        if (i >= len) break;

        if (str[i] == '"' || str[i] == '\'') {
            char quote = str[i];
            int start = i;
            i++;
            while (i < len && str[i] != quote) {
                i++;
            }
            i++;
            int token_len = i - start;
            result[index] = (char *)malloc((token_len + 1) * sizeof(char));
            if (!result[index]) {
                // Handle memory allocation failure
                for (int j = 0; j < index; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            strncpy(result[index], &str[start], token_len);
            result[index][token_len] = '\0';
        } else {
            int start = i;
            int op_len = is_operator(&str[i]);
            if (op_len > 0) {
                result[index] = (char *)malloc((op_len + 1) * sizeof(char));
                if (!result[index]) {
                    // Handle memory allocation failure
                    for (int j = 0; j < index; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                strncpy(result[index], &str[i], op_len);
                result[index][op_len] = '\0';
                i += op_len;
            } else {
                while (i < len && !isspace(str[i]) && !is_operator(&str[i]) && str[i] != '"' && str[i] != '\'') {
                    i++;
                }
                int token_len = i - start;
                result[index] = (char *)malloc((token_len + 1) * sizeof(char));
                if (!result[index]) {
                    // Handle memory allocation failure
                    for (int j = 0; j < index; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                strncpy(result[index], &str[start], token_len);
                result[index][token_len] = '\0';
            }
        }
        index++;

        while (i < len && isspace(str[i])) {
            i++;
        }
    }

    result[index] = NULL;
    return result;
}
