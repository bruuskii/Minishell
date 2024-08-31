/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:33:53 by izouine           #+#    #+#             */
/*   Updated: 2024/08/31 13:00:44 by izouine          ###   ########.fr       */
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

typedef struct s_token_info
{
	char						**result;
	int							*index;
	int							start;
	int							*i;
}								t_token_info;

extern t_exec					*g_exec;

int	handle_operator(t_cmd *new_cmd, t_token **token);
int	process_token_cmd(t_cmd *new_cmd, t_token **token, int *i);
int	allocate_cmd_array(t_cmd *new_cmd, int nbr_of_args);
int	process_cmd_tokens(t_cmd *new_cmd, t_token **token);
t_cmd	*init_new_cmd(void);
int	count_args_cmd(t_token *token);
t_filedescriptiom	*create_file_desc(t_token *token);
void	add_file_to_cmd(t_cmd *cmd, t_filedescriptiom *new_file, int is_infile);
int	handle_command_argument(t_cmd *new_cmd, t_token *token, int *i);
void	cleanup_cmd(t_cmd *cmd);
t_cmd	*parse_command_cmd(t_token **token);
t_cmd	*parse_every_command(t_token *token);
t_env	*create_env_node(char *str);
void	free_env_list(t_env *head);
t_env	*add_env_node(t_env **head, t_env **prev, char *str);
t_env	*init_env(char **str);
void	printf_dq_after(char *cmd, char c);
void	print_env(t_env *env, int isexport);
void	update_shlvl(t_env *env, const char *shlvl_prefix);
void	increment_shell_level(t_env *env);
char	*find_pwd(t_env *env);
void	update_oldpwd(t_env *env, char *pwd);
void	save_old_pwd(t_env *env);
void	save_current_pwd(t_env *env);
char	*handle_env_var(char *final, t_token *token, t_env *env, size_t *i);
char	*handle_dollar_sign(char *final, t_token *token, t_env *env, size_t *i);
char	*handle_special_command(t_token *token);
int	is_special_command(t_token *token);
char	*handle_regular_char(char *final, t_token *token, size_t *i,
		int *quotes);
char	*handle_exit_status(char *final);
char	*copy_env_value(char *final, const char *path);
char	*handle_env_variable(char *final, char *dest, t_env *env);
char	*append_char(char *final, char c);
char	*handle_quoted_dollar(char *final, t_token *token, size_t *i);
char	*process_token_loop(t_token *token, t_env *env, char *final);
char	*process_token_expand(t_token *token, t_env *env);
int	expand(t_token *token, t_env *env, char **str, int index);
int	is_space_split(char c);
int	is_operator_split(const char *str);
int	count_quote_token(const char *str, int *i, int len);
int	count_operator_token(const char *str, int *i);
int	count_word_token(const char *str, int *i, int len);
int	count_tokens_helper(const char *str, int len);
int	count_tokens_split(const char *str);
int	handle_quote_split(const char *str, int *i, char **result, int *index);
int	handle_operator_split(const char *str, int *i, char **result, int *index);
int	handle_quoted_substring(const char *str, int *i, char quote);
int	handle_dollar_quote(const char *str, int *i);
int	advance_to_end_of_word(const char *str, int *i);
int	handle_word(const char *str, int *i, char **result, int *index);
int	handle_space(char **result, int *index);
void	skip_spaces(const char *str, int *i);
int	process_token_split(const char *str, int *i, char **result, int *index);
int	process_space(const char *str, int *i, char **result, int *index);
char	**init_result(int token_count);
int	split_string_loop(const char *str, char **result);
void	free_result(char **result);
char	**split_string_helper(const char *str, int token_count);
char	**split_string(const char *str);
int	check_start_end(char *line, int len);
int	check_operators(char *line);
int	first_parse(char *line);
int	error_return(void);
int	check_outfiles(char *str, int index);
void	process_quote(char c, char *current_quote);
int	check_quotes(char *token, char *current_quote);
int	parse_every_word(char **tokens);
int	is_quote(char c);
void	grep_type_space(t_token *token);
int	is_redirect_out(t_token *token);
int	is_redirect_in(t_token *token);
int	iss_operator(char *token);
int	is_command_token(t_token *token, int index, int is_command);
void	processs_token(t_token *current, t_env *env, char **tokens, int index);
t_token	*tokenize_input(char **tokens, t_env *env);
void	grep_type(t_token *token, int index, int is_command);
void	free_string_array(char **arr);
void	free_tokens(t_token *head);
t_token	*create_new_token(char *token_str, int args_nbr);
void	link_tokens(t_token **head, t_token **current, t_token *new_token);
t_token	*tokenize_input_helper(char **tokens, t_env *env);
int	tokenize_and_parse(char **tokens, t_env *env, t_token **head, t_cmd **cmd);
int	process_tokens(char *str, t_env *env, t_token **token, t_cmd **cmd);
int	print_type(char *str, t_env *env, t_token **token, t_cmd **cmd);
void	handle_quotes_and_args(t_token *current, int *args_nbr, int index);
void	update_command_status(t_token *current, int *is_command,
		int *args_nbr);
char	*double_quotes(char *token);
char	*allocate_token(const char *str, int start, int len);





int								cd(char **cmd);
char							*ft_itoa(int n);
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
int								getoutputfile(t_cmd *cmd, t_exec_utils *exec_utils);
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

#endif
