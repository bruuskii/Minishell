/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:33:53 by izouine           #+#    #+#             */
/*   Updated: 2024/08/26 19:22:22 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define RESET "\033[0m"
# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define WHITE "\033[0;37m"

typedef struct s_token
{
	char						*token;
	char						*type;
	int							nbr_of_args;
	struct s_token				*next;
	struct s_token				*prev;
}								t_token;

typedef struct s_env
{
	char						*line;
	struct s_env				*next;
	struct s_env				*prev;
}								t_env;

typedef struct s_token_process
{
	char						*token;
	char						*new_token;
	int							i;
	int							pos;
	int							fully_quoted;
}								t_token_process;

typedef struct s_filedescriptiom
{
	char						*filename;
	int							isherdoc;
	int							iswithappend;
	char						*delimeter;
	struct s_filedescriptiom	*next;
}								t_filedescriptiom;

typedef struct s_cmd
{
	char						**cmd;
	struct s_filedescriptiom	*infile;
	struct s_filedescriptiom	*outfile;
	struct s_cmd				*next;
	int							*fd;
	int							cleanup_ready;
}								t_cmd;

typedef struct s_exec_utils
{
	t_filedescriptiom			*file;
	int							countpipes;
	int							i;
	int							pid;
	int							fdin;
	int							savedout;
	int							fdout;
	int							its_builtin;
	int							exit_state;
	int							sig_rec;
}								t_exec_utils;

typedef struct s_exec
{
	t_token						*tokens;
	t_cmd						*cmd;
	char						**paths;
	t_env						*env;
	int							exit_status;
	int							herdoc_sig;
}								t_exec;

extern t_exec					*g_exec;

char							**split_string(const char *str);
int								is_operator(const char *str);
int								parse_every_word(char **tokens);
char							*double_quotes(char *tokens);
int								cd(char **cmd);
void							print_env(t_env *env, int isexport);
t_env							*init_env(char **str);
void							increment_shell_level(t_env *env);
char							*ft_itoa(int n);
void							save_old_pwd(t_env *env);
void							save_current_pwd(t_env *env);
void							grep_type(t_token *token, int index,
									int command);
t_cmd							*parse_every_command(t_token *token);
int								print_type(char *str, t_env *env,
									t_token **token, t_cmd **cmd);
int								expand(t_token *token, t_env *env, char **str,
									int index);
int								first_parse(char *line);
int								error_return(void);
int								check_outfiles(char *str, int index);
void							insertatend(t_env **head, t_env *node_to_add);
void							delete_env_node(t_env **head,
									t_env *NodeToDelete);
void							delete_token_node(t_token **head,
									t_token *NodeToDelete);
void							free_db_arr(char **arr);
void							delete_cmd_node(t_cmd **head,
									t_cmd *NodeToDelete);
void							delete_env(void);
void							delete_tokens(void);
void							delete_cmds_node(void);
void							delete_fd_nodes(t_filedescriptiom **src);
void							delete_fd_node(t_filedescriptiom **head,
									t_filedescriptiom *NodeToDelete);
void							free_exec(int isexit);
t_env							*is_in_env(t_env *env, char *value_to_check);
int								getequalindex(char *cmd);
void							export(char **cmd);
void							unset(char **cmd);
void							pwd(void);
void							echo(char **cmd);
void							ft_exit(char **cmd);
void							execute(t_exec *exec);
t_exec							*initexec(char **env);
char							**get_paths(void);
int								count_pipes(t_cmd *cmd);
int								countfiles(t_filedescriptiom *files);
char							*get_path(char *cmd);
int								heredoc(char *delimeter, int fd);
char							**init_env_arr(void);
void							handle_sigint(int test);
void							cleanup_commands(t_cmd *cmd_head);
int								getoutputfile(t_cmd *cmd,
									t_exec_utils *exec_utils);
int								getinputfile(t_cmd *cmd,
									t_exec_utils *exec_utils);
int								execute_herdoc(t_exec_utils *exec_utils,
									int *fileinfd);
void							set_upfdfiles(int fdin, int fdout, t_cmd *cmd,
									t_cmd *prev);
void							get_exitstatus(t_exec_utils exec_utils);
t_exec_utils					init_exec_utils(t_cmd *cmd);
void							ft_execute(t_exec_utils *exec_utils, t_cmd *cmd,
									t_cmd *prev);
int								itsbuiltin(t_cmd *cmd);
void							ft_exec_no_path(t_cmd *cmd, char **env,
									char *commandpath);
void							ft_exec(t_cmd *cmd);
void							ft_exec_builtin(t_cmd *cmd);
void							exit_with_message(char *s, int exit_value);
int								ft_heredoc(char *delimeter, int fd, char *tmp);
void							ft_export2(char *cmd, int indexofequal);
void							add_to_env(t_env *temp, int isappend,
									char *cmd);
void							update_in_env(t_env *temp, char *word_to_app,
									int isappend, char *cmd);
int								getequalindex(char *cmd);
char							*remove_char_(char *str, char c);
t_env							*is_in_env(t_env *env, char *value_to_check);
void							insertatend(t_env **head, t_env *node_to_add);

#endif
