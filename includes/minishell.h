/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:31:02 by hkhrayza          #+#    #+#             */
/*   Updated: 2025/01/25 09:13:48 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../mylib/libft/libft.h"
# include "arts.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/syscall.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>

/*
** Macros to define some error messages
*/

# define ERROR_PIPE "minishell: syntax error near unexpected token `|'\n"
# define ERROR_DIR "No such file or Directory\n"
# define ERROR_HOME "minishell: cd: HOME not set\n"
# define ERROR_CMD "command not found\n"
# define MAX_LINE 1024
# define MAX_ARGS 64
# define BUFFER_SIZE 1024
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define ECHOCTL 0001000

/*
** ENUM ------------
*/

typedef enum e_tokens
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_EOF
}						t_tokens;

typedef enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTES,
	DOUBLE_QUOTES,
	QUOTE_ERROR
}						t_quote_type;

/*
** structures ----------
*/

typedef struct s_env
{
	char				*key;
	char				*value;
	int					hidden;
	struct s_env		*next;
}						t_env;

typedef struct s_lexer
{
	char				*str;
	int					i;
	int					space;
	t_tokens			token;
	t_quote_type		quote_type;
	struct s_lexer		*next;
}						t_lexer;

typedef struct s_command
{
	t_lexer				*tokens;
	int					(*builtin)(struct s_command *, t_env *);
	t_lexer				*redirects;
	char				**heredoc_delimiters;
	int					heredoc_fd;
	struct s_command	*prev;
	struct s_command	*next;
}						t_command;

typedef struct s_cmd
{
	int					last_exit_status;
	t_lexer				*lexer;
	t_command			*parser;
	t_lexer				*incomplete_command;
	t_env				*envp;
}						t_cmd;

typedef struct s_context
{
	int					flag_space;
	int					exp;
	t_cmd				*cmd;
}						t_context;

typedef struct s_sig
{
	int					sigint;
	int					sigquit;
	int					sigtstp;
	int					exitstatus;
	int					g_heredoc_interrupted;
}						t_sig;

typedef struct s_process_data
{
	t_quote_type		quote_type;
	int					flag_space;
	char				*token_start;
}						t_process_data;

typedef struct s_quote_context
{
	t_quote_type		quote_type;
	int					flag_space;
}						t_quote_context;

typedef struct s__pip
{
	t_command			*cmd;
	t_cmd				*context;
	int					*pipes;
	int					pipe_count;
}						t_pip;

extern t_sig			g_sig;

/* Signal functions */

void					disable_ctrl_c(void);
void					enable_ctrl_c(void);
void					sig_int(int code);
void					sig_tstp(int code);
void					sig_quit(int code);
void					sig_init(void);
void					init_heredoc_signals(void);
void					reset_signals_after_heredoc(void);

/* cleaning functions */

void					cleanup(t_cmd *context);
void					free_paths(char **paths);
void					free_my_env(t_env *env);
void					free_command(t_command *cmd);
void					free_sorted_env(t_env *env);
void					free_array(char **array);
void					free_lexer(t_lexer *lexer);
void					free_command_list(t_command *cmd_list);
void					free_tokens(t_lexer *tokens);
void					free_heredoc_delimiters(char **heredoc_delimiters);

/* Printing functions */

void					print_lexer(t_lexer *lexer);
void					print_commands(t_command *cmd_list);
void					print_lexerr(t_lexer *lexer);
void					print_parser(t_command *parser);
void					print_welcome_message(void);
void					print_array(char **cmd);
void					print_command(t_command *command);
int						handle_append(t_command *cmd);
int						handle_output(t_command *cmd);
int						handle_input(t_command *cmd);

/* Boolean functions */

int						contains_input_redirection(t_lexer *token);
int						contains_output_redirection(t_lexer *token);
int						contains_append(t_lexer *token);
int						contains_heredoc(t_lexer *token);
int						contains_redirection(t_lexer *tokens);
int						contains_pipes(t_lexer *token);
int						is_directory(char *path);
void					handle_digits(t_lexer **lexer, char *line, int *i);

/* Builtin functions */

void					builtin_unset(char **args, t_env **envp);
void					builtin_env(t_env *envp);
void					builtin_echo(char **args);
void					builtin_pwd(void);
void					builtin_exit(t_command *cmd, t_cmd *context);
void					builtin_export(char **args, t_env *envp);
void					builtin_cd(char **args, t_env *envp);
int						is_builtin(char *cmd);

/* Execution functions */

int						execution(t_command *cmd, t_cmd *context);
int						handle_command(t_command *cmd, t_cmd *context,
							int flage);
void					execute_builtin_command(t_command *cmd, t_cmd *context);
char					**lexer_to_args(t_lexer *tokens);
void					exec_command(char *cmd_path, char **args, t_cmd *cmd);
void					execute_external_command(char **args, t_cmd *cmd);
void					remove_redirection_tokens(t_lexer **tokens,
							t_lexer *redirection, t_lexer *file_token);
void					restore_fds(int *backup_fds);
void					remove_token(t_lexer **tokens,
							t_lexer *token_to_remove);
int						handle_flag_or_heredoc(t_command *cmd, t_cmd *context,
							int flage, int *backup_fds);

/* Getting functions */

char					*get_env_var(t_env *env, const char *key);
char					*get_target_directory(char **args, t_env *envp);
char					*get_relative_path(char *pwd, char *home);
char					*get_command_path(char **args, t_cmd *cmd);
char					*get_path_from_env(t_env *envp);
char					*get_input_file(t_lexer *token);
char					*get_output_file(t_lexer *token);
char					*get_heredoc_delimiter(t_lexer *token);
char					*get_append_file(t_lexer *token);
char					*find_command_path(char *command, t_cmd *cmd);

/* Enviroment functions */

void					add_to_sorted_env(t_env **sorted_env, char *key,
							char *value, int hidden);
void					add_env_to_sorted_list(t_env **sorted, t_env *envp);
void					swap_env_nodes(t_env *current);
void					remove_env_var(char *key, t_env **envp);
void					print_sorted_env_vars(t_env *envp);
void					add_env_var(t_env *envp, char *key, char *value,
							int hidden);
void					set_env_var(t_env *envp, char *key, char *value);
void					set_env_var_hidden(t_env *envp, char *key, char *value,
							int hidden);

t_env					*bubble_sort_env(t_env *sorted);
t_env					*sort_env(t_env *envp);
t_env					*create_env_node(char *env_var);
t_env					*initialize_env_list(char **envp);
t_env					*my_env(char **envp);
t_command				*parser(t_lexer *lexer);
void					change_directory(char *dir, t_env *envp);
void					process_export_argument(char *arg, t_env *envp);

/* Lexer functions */

int						count_tokens(t_lexer *tokens);
t_lexer					*lexer(char *line, t_cmd *cmd);
t_lexer					*init_lexer_token(char *str, t_tokens token,
							t_quote_type quote_type);
void					add_lexer_token(t_lexer **lexer, t_lexer *new_token);
int						process_quotes(t_lexer **lexer, t_process_data *data,
							int j);

/* Main functions */

char					*ft_strjoin_three(char const *s1, char const *s2,
							char const *s3);
char					**env_list_to_array(t_cmd *cmd);
char					*create_full_path(char *directory, char *command);
void					initialize_context(t_cmd *context, char **envp);
char					*generate_prompt(t_cmd *context);
void					process_input(char *line, t_cmd *context);
char					*read_input(t_cmd *context);

/* Handling  functions */

void					handle_user_input(t_cmd *context);
void					handle_pipe(t_lexer **lexer, char *line, int *i);
void					handle_dollar(t_lexer **lexer, char *line, int *i,
							t_context *ctx);
void					handle_redirection_token(t_lexer **lexer, char *line,
							int *i);
void					handle_word(t_lexer **lexer, char *line, int *i,
							int flag_space);
int						handle_quotes(t_lexer **lexer, char *line, int *i,
							t_quote_context quote_ctx);
void					handle_token(t_lexer **lexer, char *line, int *i,
							t_context *ctx);

int						handle_heredocs(t_command *cmd, char ***temp_filenames,
							int *temp_file_count);
int						handle_redirections(t_command *cmd, t_cmd *context);
void					*handle_directory(char *oldpwd);

/*Parser2*/

void					add_command(t_command **cmd_list, t_command *new_cmd);
void					handle_placeholder_token(t_command *current_cmd);
void					handle_pipe_token(t_command **cmd_list,
							t_command **current_cmd);
void					handle_other_token(t_command **current_cmd,
							t_lexer *current_token);
void					add_token_to_command(t_command *cmd, t_lexer *token);
t_command				*init_command(void);

/*piping norm*/

char					**create_argv(t_lexer *tokens, int *argc);
int						handle_command_redirections(t_command *cmd,
							t_cmd *context, char **argv);
void					execute_command(t_command *cmd, t_cmd *context);

/*Handling5*/

void					handle_dollar_pid(t_lexer **lexer, int *i);
void					handle_dollar_exit_status(t_lexer **lexer, int *i,
							t_cmd *cmd);
void					handle_dollar_variable(t_lexer **lexer, char *line,
							int *i, t_context *ctx);
/*Handling3*/

char					*extract_word(char *line, int *i);
void					merge_or_add_token(t_lexer **lexer, char *new_token);
void					handlespace(t_context *ctx, int *i);
int						handlequotetoken(t_lexer **lexer, char *line, int *i,
							t_context *ctx);
void					handledollartoken(t_lexer **lexer, char *line, int *i,
							t_context *ctx);
void					handlered(t_lexer **lexer, char *line, int *i,
							t_context *ctx);
void					handlepipetoken(t_lexer **lexer, char *line, int *i,
							t_context *ctx);
void					handlewordtoken(t_lexer **lexer, char *line, int *i,
							t_context *ctx);
/* boolredirection*/

int						is_invalid_filename(const char *filename);
int						is_herdoc(t_lexer *current);
int						is_output_redirection(t_lexer *current);
int						is_append_redirection(t_lexer *current);
int						is_input_redirection(t_lexer *current);
int						herdoo(t_command *cmd);
int						is_herdoc_redirection(t_lexer *current);
int						is_herdoc(t_lexer *current);

/* Utility functions */

char					**allocate_args(int count);
void					process_pipes(t_command *cmd, t_cmd *context);
void					execute_command_with_heredoc(t_command *cmd,
							t_cmd *context);
pid_t					ft_getpid(void);
int						count_tokens(t_lexer *tokens);

void					process_heredoc_input(int temp_fd, char *buffer,
							char *delimiter);
void					handle_env_variable(int temp_fd, char *buffer);
void					process_heredoc(int temp_fd, char *delimiter);
int						handle_single_heredoc(t_lexer **tokens,
							char ***temp_filenames, int *temp_file_count);
void					redirect_temp_files(char **temp_filenames,
							int temp_file_count);
void					cleanup_temp_files(char **temp_filenames,
							int temp_file_count);
int						handle_heredoc_error(t_lexer **tokens, char *message,
							int move_next);
int						create_temp_file(char *filename);
void					store_temp_filename(char ***temp_filenames,
							int *temp_file_count, char *filename);
void					remove_heredoc_tokens(t_command *cmd);
void					close_and_wait(int *pipes, int pipe_count);
void					handle_error_and_exit(const char *message);
int						count_commands(t_command *cmd_list);

#endif
