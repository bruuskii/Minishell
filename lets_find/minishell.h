/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:33:53 by izouine           #+#    #+#             */
/*   Updated: 2024/08/18 15:48:15 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/history.h>
# include "Libft/libft.h"
# include <fcntl.h>
# include <limits.h>

# define RESET "\033[0m"
# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define WHITE "\033[0;37m"

typedef struct s_token
{
	char			*token;
	char			*type;
	int				nbr_of_args;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_env
{
	char			*line;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_token_process
{
	char			*token;
	char			*new_token;
	int				i;
	int				pos;
	int				fully_quoted;
}					t_token_process;

typedef struct s_filedescriptiom
{
	char						*filename;
	int							isherdoc;
	int							iswithappend;
	char						*delimeter;
	struct s_filedescriptiom	*next;
}					t_filedescriptiom;

typedef struct s_cmd
{
    char **cmd;
    struct s_filedescriptiom *infile;
    struct s_filedescriptiom *outfile;
    struct s_cmd *next;
    int *fd;
}   t_cmd;


typedef struct s_exec_utils
{

    int countpipes;
    int i;
    int pid;
    int fdin;
    int savedout;
    int fdout;
    int its_builtin;
}   t_exec_utils;




typedef struct s_exec
{
	t_token				*tokens;
	t_cmd				*cmd;
	char				**paths;
	t_env				*env;
	int					exit_status;
}					t_exec;

extern t_exec		*g_exec;

char				**split_string(const char *str);
int					is_operator(const char *str);
int					parse_every_word(char **tokens);
char				*double_quotes(char *tokens);
int					cd(char **cmd);
void				print_env(t_env *env, int isexport);
t_env				*init_env(char **str);
void				increment_shell_level(t_env *env);
char				*ft_itoa(int n);
void				save_old_pwd(t_env *env);
void				save_current_pwd(t_env *env);
void				grep_type(t_token *token, int index, int command);
t_cmd				*parse_every_command(t_token *token);
int					print_type(char *str, t_env *env, t_token **token,
						t_cmd **cmd);
int					expand(t_token *token, t_env *env, char **str, int index);
int					first_parse(char *line);
int					error_return(void);
int					check_outfiles(char *str, int index);
void				InsertAtEnd(t_env **head, t_env *node_to_add);
void				Delete_env_Node(t_env **head, t_env *NodeToDelete);
void				Delete_token_Node(t_token **head, t_token *NodeToDelete);
void				free_db_arr(char **arr);
void				Delete_cmd_Node(t_cmd **head, t_cmd *NodeToDelete);
void				Delete_env(void);
void				Delete_tokens(void);
void				Delete_cmds_node(void);
void				Delete_fd_Nodes(t_filedescriptiom **src);
void				free_exec(int isexit);
t_env				*is_in_env(t_env *env, char *value_to_check);
int					getequalindex(char *cmd);
void				export(char **cmd);
void				unset(char **cmd);
void				pwd(void);
void				echo(char **cmd);
void				ft_exit(char **cmd);
void				execute(t_exec *exec, char **env);
t_exec				*initexec(char **env);
char				**get_paths(void);
int					count_pipes(t_cmd *cmd);
int					countfiles(t_filedescriptiom *files);
char				*get_path(char *cmd);
int					heredoc(char *delimeter);

#endif