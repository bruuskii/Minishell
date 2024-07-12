#ifndef MINISHELL_H
#define MINISHELL_H



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/history.h>

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
    int nbr_of_args;
    struct s_token *next;
    struct s_token *prev;
}               t_token;

typedef struct s_env
{
    char *line;
    struct s_env *next;
    struct s_env *prev;
}               t_env;


char **split_string(const char *str);
int	is_operator(const char *str);
int parse_every_word(char **tokens);
char  **double_quotes(char **tokens);
int cd_builtin(const char *path, t_env *env);
void pwd(t_env *env);
void    print_env(t_env *env);
t_env *init_env(char **str);
void increment_shell_level(t_env *env);
char	*ft_itoa(int n);
void save_old_pwd(t_env *env);
void save_current_pwd(t_env *env);
void grep_type(t_token *token, int index, int command);
int print_type(char *str, t_env *env, t_token *token);




#endif
