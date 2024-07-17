#include "minishell.h"

int first_parse(char *line)
{
    int i = 0;
    int len = strlen(line) - 1;
    while (isspace(line[i]))
        i++;
    if (is_operator(&line[i]))
        return error_return();
    while (len > 0 && isspace(line[len]))
        len--;
    if (is_operator(&line[len]))
        return error_return();
    while (line[i])
    {
        int op_len = is_operator(&line[i]);
        if (op_len && check_outfiles(line, i))
        {
            if (is_operator(&line[i + op_len]))
                return error_return();
        }
        i++;
    }
    return 1;
}

int error_return()
{
    printf("bash: Syntax error near \\n\n");
    return 0;
}

int check_outfiles(char *str, int index)
{
    if(str[index] == '>' && str[index + 1] == '>' && str[index + 2] == '>')
        return 1;
    return 0;
}