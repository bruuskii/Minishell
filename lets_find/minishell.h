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
#include "Libft/libft.h"
#include <fcntl.h>

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





typedef struct s_filedescriptiom
{

    char    *filename;
    int     isherdoc;
    int     iswithappend;
    char    *delimeter;
    struct s_filedescriptiom *next;
}               t_filedescriptiom;


typedef struct s_cmd
{
    char **cmd;
    struct s_filedescriptiom *infile;
    struct s_filedescriptiom *outfile;
    struct s_cmd *next;
    int *fd;
}   t_cmd;







typedef struct s_exec
{
    t_token *tokens;
    t_cmd *cmd;
    char **Paths;
    t_env *env;
    t_env *env_export;
    int exit_status;
}   t_exec;


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
t_cmd *parse_every_command(t_token *token);
int print_type(char *str, t_env *env, t_token **token, t_cmd **cmd);

int expand(t_token *token, t_env *env, char **str, int index);
int first_parse(char *line);
int error_return();
int check_outfiles(char *str, int index);

void    InsertAtEnd(t_env **head, t_env *node_to_add);
void export(t_exec *exec, char **cmd);
//exec;

void execute( t_exec *exec, char **env);
t_exec *initexec(char **env);
char	**get_paths();
int count_pipes(t_cmd *cmd);
int countfiles(t_filedescriptiom *files);
char	*get_path(t_exec *exec, char *cmd);
int heredoc(char *delimeter);




#endif
