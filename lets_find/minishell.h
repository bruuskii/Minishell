#ifndef MINISHELL_H
#define MINISHELL_H



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define RESET "\033[0m"
#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define WHITE "\033[0;37m"

extern const char	*operations[];
extern int			num_operations;

typedef struct s_token
{
    char *token;
    char *type;
}               t_token;

char **split_string(const char *str);
int	is_operator(const char *str);
int  print_type(char *str);
int parse_every_word(char **tokens);
char  **double_quotes(char **tokens);














#endif
