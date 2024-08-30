/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:33:53 by izouine           #+#    #+#             */
/*   Updated: 2024/08/30 17:08:14 by izouine          ###   ########.fr       */
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

typedef struct s_process_info
{
	size_t						i;
	int							in_s_quote;
	int							in_d_quote;
	size_t						token_len;
}								t_process_info;

typedef struct s_token_info
{
	const char					*str;
	int							*i;
	char						**result;
	int							*index;
}								t_token_info;

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
	int							fd[2];
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
int								getoutputfile(t_cmd *cmd);
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
void							cleanup_commands(t_cmd *cmd_head);
char							**split_string(const char *str);

// f_split_utils.c
int								is_space(char c);
int								is_operator(const char *str);
char							*allocate_token(const char *str, int start,
									int len);
void							skip_spacess(const char *str, int *i);

// f_split_count.c
int								count_tokens(const char *str);

// f_split_process.c
int								process_tokenn(t_token_info *info);
int								process_space(t_token_info *info);

// f_split_handlers.c
int								handle_quote(t_token_info *info);
int								handle_operator(t_token_info *info);
int								handle_word(t_token_info *info);
int								handle_space(t_token_info *info);

t_cmd							*parse_every_command(t_token *token);

// Utility functions
t_cmd							*init_new_cmd(void);
int								count_args(t_token *token);
void							skip_spaces(t_token **token);
void							free_cmd(t_cmd *cmd);

// File descriptor functions
t_filedescriptiom				*create_file_desc(t_token *token);
void							add_file_to_cmd(t_cmd *cmd,
									t_filedescriptiom *new_file, int is_infile);

// Token processing functions
t_filedescriptiom				*process_operator(t_token **token,
									int is_heredoc, int is_append);
int								process_command_or_argument(t_cmd *new_cmd,
									t_token **token, int *i);
int								process_operator_token(t_cmd *new_cmd,
									t_token **token);
int								process_token(t_cmd *new_cmd, t_token **token,
									int *i);

// Command parsing functions
t_cmd							*allocate_new_cmd(int nbr_of_args);
t_cmd							*parse_command_tokens(t_cmd *new_cmd,
									t_token **token);
t_cmd							*parse_command(t_token **token);

int								expand(t_token *token, t_env *env, char **str,
									int index);

// Helper functions
char							*handle_exit_status(char *final);
char							*copy_env_value(char *final, const char *path);
char							*handle_env_variable(char *final, char *dest,
									t_env *env);
char							*append_char(char *final, char c);

// Dollar sign handling
char							*handle_dollar_quote(char *final,
									t_token *token, size_t *i);
char							*handle_dollar_var(char *final, t_token *token,
									t_env *env, size_t *i);
char							*handle_dollar_sign(char *final, t_token *token,
									t_env *env, size_t *i);

// Special cases
char							*handle_special_command(t_token *token);
char							*handle_quotes(char *final, char c,
									int *in_quote);

// Processing functions
char							*process_char(char *final, t_token *token,
									t_env *env, t_process_info *info);
char							*process_token_loop(t_token *token, t_env *env,
									char *final);
char							*process_tokennn(t_token *token, t_env *env);

// Main functions
t_env							*init_env(char **str);
void							print_env(t_env *env, int isexport);
void							increment_shell_level(t_env *env);
void							save_old_pwd(t_env *env);
void							save_current_pwd(t_env *env);

// Helper functions
t_env							*create_env_node(char *str);
void							free_env_list(t_env *head);
t_env							*add_env_node(t_env **head, t_env **prev,
									char *str);
void							printf_dq_after(char *cmd, char c);
void							update_shlvl(t_env *env,
									const char *shlvl_prefix);
char							*find_pwd(t_env *env);
void							update_oldpwd(t_env *env, char *pwd);

int								parse_every_word(char **tokens);
t_token							*tokenize_input(char **tokens, t_env *env);
int								print_type(char *str, t_env *env,
									t_token **token, t_cmd **cmd);

// Token processing functions
void							grep_type(t_token *token, int index,
									int is_command);
char							*double_quotes(char *token);

// Helper functions
void							free_string_array(char **arr);
void							free_tokens(t_token *head);
t_token							*create_new_token(char *token_str,
									int args_nbr);
void							update_args_and_command(t_token *current,
									int index, int *args_nbr, int *is_command);
void							processs_token(t_token *current, t_env *env,
									char **tokens, int index);
void							link_tokens(t_token **head, t_token **current,
									t_token *new_token);
int								initialize_print_type(char *str,
									char ***tokens);
int								finalize_print_type(t_token *head, t_cmd **cmd);
void							grep_type_space(t_token *token);
int								is_quote(char c);

// Additional helper functions (to be implemented in separate files)
int								is_output_redirection(t_token *token);
int								is_input_redirection(t_token *token);
int								is_token_operator(t_token *token);
int								is_token_command(t_token *token, int index,
									int is_command);

void							process_quote(char c, char *current_quote);
int								check_quotes(char *token, char *current_quote);
#endif
