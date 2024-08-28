#include "minishell.h"

static int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

int is_operator(const char *str)
{
    const char *operations[] = {"<<", "<", ">>", ">", "|"};
    int num_operations = sizeof(operations) / sizeof(operations[0]);
    
    for (int k = 0; k < num_operations; k++)
    {
        int op_len = ft_strlen(operations[k]);
        if (ft_strncmp(str, operations[k], op_len) == 0)
        {
            if (!(str[0] == '$' && (str[1] == '\'' || str[1] == '"')))
                return op_len;
        }
    }
    return 0;
}

static int count_quote_token(const char *str, int *i, int len)
{
    char quote = str[*i];
    (*i)++;
    while (*i < len && str[*i] != quote)
        (*i)++;
    if (*i < len)
        (*i)++;
    return 1;
}

static int count_operator_token(const char *str, int *i)
{
    int op_len = is_operator(&str[*i]);
    if (op_len > 0)
    {
        *i += op_len;
        return 1;
    }
    return 0;
}

static int count_word_token(const char *str, int *i, int len)
{
    while (*i < len && !is_space(str[*i]) && !is_operator(&str[*i])
        && str[*i] != '"' && str[*i] != '\'')
        (*i)++;
    return 1;
}

static int count_tokens_helper(const char *str, int len)
{
    int i = 0;
    int count = 0;

    while (i < len)
    {
        while (i < len && is_space(str[i]))
            i++;
        if (i >= len)
            break;
        if (str[i] == '"' || str[i] == '\'')
            count += count_quote_token(str, &i, len);
        else if (count_operator_token(str, &i))
            count++;
        else
            count += count_word_token(str, &i, len);
        if (i < len && is_space(str[i]))
            count++;
        while (i < len && is_space(str[i]))
            i++;
    }
    return count;
}

static int count_tokens(const char *str)
{
    if (!str)
        return 0;
    return count_tokens_helper(str, ft_strlen(str));
}

static char *allocate_token(const char *str, int start, int len)
{
    char *token = (char *)malloc((len + 1) * sizeof(char));
    if (!token)
        return NULL;
    ft_strlcpy(token, &str[start], len + 1);
    return token;
}

static int handle_quote(const char *str, int *i, char **result, int *index)
{
    int start = (*i > 0 && str[*i - 1] == '$') ? *i - 1 : *i;
    char quote = str[*i];
    (*i)++;
    while (str[*i] && str[*i] != quote)
        (*i)++;
    if (str[*i])
        (*i)++;
    int token_len = *i - start;
    result[*index] = allocate_token(str, start, token_len);
    if (!result[*index])
        return 0;
    (*index)++;
    return 1;
}

static int handle_operator(const char *str, int *i, char **result, int *index)
{
    int op_len = is_operator(&str[*i]);
    if (op_len > 0)
    {
        result[*index] = allocate_token(str, *i, op_len);
        if (!result[*index])
            return 0;
        *i += op_len;
        (*index)++;
    }
    return 1;
}

static int handle_word(const char *str, int *i, char **result, int *index)
{
    int start = *i;
    while (str[*i] && !is_space(str[*i]) && !is_operator(&str[*i]))
    {
        if (str[*i] == '$' && (str[*i + 1] == '\'' || str[*i + 1] == '"'))
        {
            char quote = str[*i + 1];
            *i += 2;
            while (str[*i] && str[*i] != quote)
                (*i)++;
            if (str[*i])
                (*i)++;
        }
        else if (str[*i] != '"' && str[*i] != '\'')
            (*i)++;
        else
            break;
    }
    int token_len = *i - start;
    result[*index] = allocate_token(str, start, token_len);
    if (!result[*index])
        return 0;
    (*index)++;
    return 1;
}

static int handle_space(char **result, int *index)
{
    result[*index] = allocate_token(" ", 0, 1);
    if (!result[*index])
        return 0;
    (*index)++;
    return 1;
}

static void skip_spaces(const char *str, int *i)
{
    if (!str || !i)
        return;
    while (str[*i] && is_space(str[*i]))
        (*i)++;
}

static int process_token(const char *str, int *i, char **result, int *index)
{
    if (str[*i] == '"' || str[*i] == '\'')
        return handle_quote(str, i, result, index);
    else if (is_operator(&str[*i]))
        return handle_operator(str, i, result, index);
    else
        return handle_word(str, i, result, index);
}

static int process_space(const char *str, int *i, char **result, int *index)
{
    if (str[*i] && is_space(str[*i]))
    {
        if (!handle_space(result, index))
            return 0;
        (*i)++;
    }
    return 1;
}

static char **init_result(int token_count)
{
    char **result = (char **)malloc((token_count + 1) * sizeof(char *));
    if (!result)
        return NULL;
    return result;
}

static int split_string_loop(const char *str, char **result)
{
    int i = 0;
    int index = 0;
    int skip_space = 1;

    if (!str || !result)
        return 0;

    while (str[i])
    {
        if (skip_space && str[i])
            skip_spaces(str, &i);
        if (!str[i])
            break;
        if (!process_token(str, &i, result, &index))
            return 0;
        if (!skip_space && !process_space(str, &i, result, &index))
            return 0;
        skip_space = 0;
        skip_spaces(str, &i);
    }
    result[index] = NULL;
    return 1;
}

static void free_result(char **result)
{
    if (!result)
        return;
    for (int i = 0; result[i]; i++)
        free(result[i]);
    free(result);
}

static char **split_string_helper(const char *str, int token_count)
{
    char **result = init_result(token_count);
    if (!result)
        return NULL;
    if (!split_string_loop(str, result))
    {
        free_result(result);
        return NULL;
    }
    return result;
}

char **split_string(const char *str)
{
    if (!str)
        return NULL;

    int token_count = count_tokens(str);
    if (token_count <= 0)
        return NULL;

    return split_string_helper(str, token_count);
}