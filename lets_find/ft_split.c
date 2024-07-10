#include "minishell.h"

const char	*operations[] = {"<<", "<", ">>", ">", "|", "$"};
int			num_operations = sizeof(operations) / sizeof(operations[0]);

int	is_operator(const char *str)
{
	int	op_len;

	for (int k = 0; k < num_operations; k++)
	{
		op_len = strlen(operations[k]);
		if (strncmp(str, operations[k], op_len) == 0)
		{
			return (op_len);
		}
	}
	return (0);
}

char **split_string(const char *str) {
    int i = 0, count = 0;
    int len = strlen(str);
    while (i < len) {
        while (i < len && isspace(str[i])) {
            i++;
        }

        if (i >= len) break;

        int op_len = is_operator(&str[i]);
        if (op_len > 0) {
            count++;
            i += op_len;
        } else {
            while (i < len && !isspace(str[i]) && !is_operator(&str[i])) {
                i++;
            }
            count++;
        }

        while (i < len && isspace(str[i])) {
            i++;
        }
    }

    char **result = (char **)malloc((count + 1) * sizeof(char *));
    i = 0;
    int index = 0;

    while (i < len) {
        while (i < len && isspace(str[i])) {
            i++;
        }

        if (i >= len) break;

        int start = i;
        int op_len = is_operator(&str[i]);
        if (op_len > 0) {
            result[index] = (char *)malloc((op_len + 1) * sizeof(char));
            strncpy(result[index], &str[i], op_len);
            result[index][op_len] = '\0';
            i += op_len;
        } else {
            while (i < len && !isspace(str[i]) && !is_operator(&str[i])) {
                i++;
            }
            int token_len = i - start;
            result[index] = (char *)malloc((token_len + 1) * sizeof(char));
            strncpy(result[index], &str[start], token_len);
            result[index][token_len] = '\0';
        }
        index++;

        while (i < len && isspace(str[i])) {
            i++;
        }
    }

    result[index] = NULL;
    return result;
}