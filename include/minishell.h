#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define INV_ARG_ERR "Error: invalid input"
# define MALLOC_ERR "Error: malloc failed"
# define SIGINT_ERR "ERROR registering SIGINT handler"
# define SIGQUIT_ERR "ERROR registering SIGQUIT handler"
# define PATH_UPDATE_ERR "Error updating the path"
# define DIR_ACCESS_ERR "Error accessing directory"
# define NO_FILE_ERR "Error: no such file or directory"
# define CD_TOO_MANY_ARGS_ERR "minishell: cd: too many arguments"
# define CD_NO_HOME_ERR "minishell: cd: HOME not set"
# define NO_PATH_ERR "Error getting the path"
# define UN_TOKEN_NL_ERR "minishell: syntax error near unexpected token `newline'"
# define UN_TOKEN_PIPE_ERR "minishell: syntax error near unexpected token `|'"
# define UN_TOKEN_2PIPE_ERR "minishell: syntax error near unexpected token `||'"

typedef enum e_interactive
{
	NON_INTERACTIVE,
	INTERACTIVE,
	INT_HERE_DOC
} t_interactive;

extern t_interactive g_interactive;

typedef enum e_token_type
{
	WORD,
	IN,
	HERE_DOC,
	OUT,
	APPEND,
	PIPE
} t_token_type;

typedef struct s_io
{
	int in;
	int out;
	int com_count;
} t_io;

typedef struct s_pipe
{
	int **pipes;
	int nb_pipes;
} t_pipe;

typedef struct s_token
{
	t_token_type type;
	char *data;
	struct s_token *next;
} t_token;

typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_shell
{
	char *path;
	char *oldpath;
	int last_exit_status;
	int *pids;
	int launched_procs;
	t_pipe *pipes;
	t_token **token;
	t_env **env;
} t_shell;

void init_minishell(t_shell **shell, char **envp);
void set_signal(void);
int pipeline(t_shell *shell);
int process_command(char **cmdargs, t_shell *shell, int i, t_io *io);
t_io *get_io(t_token *segment, int com_count);
void exec_bin(t_shell *shell, char **cmdargs);
int process_input_redirections(t_token *token);
int process_output_redirections(t_token *token);
int process_here_doc(char *delimiter);
int process_in(char *file);
int process_out(char *file);
int process_append(char *file);
int exec_built_in(t_shell *minishell, char **cmdargs, int out);
int cmd_is_builtin(char *cmd);
int ft_pwd(t_shell *minishell, int out);
int ft_cd(t_shell *shell, char **cmdargs);
int ft_echo(char **cmdargs, int out);
int ft_env(t_shell *minishell, int out);
int ft_export(t_shell *minishell, char **cmdargs, int out);
int ft_unset(t_shell *shell, char **cmdargs);
int ft_exit(t_shell *shell, char **cmdargs);
void get_token(char *line, t_shell *shell);
void append_token(char *data, t_token_type type, t_shell *shell);
char *trim_quotes_and_expand(char *word, t_shell *shell);
int ft_isspace(char c);
int isseparator(char c);
int verify_token(t_token **token);
char *expand_variable(char *data, t_shell *shell);
t_pipe *init_pipes(t_token *token);
void set_pipes(t_shell *shell, t_io *io);
void close_pipes(t_pipe *pipes);
void free_pipes(t_pipe *pipes);
int upsert_env(t_shell *shell, char *envp);
int is_valid_env_var(char *str);
t_env *find_env_var_by_name(t_shell *shell, char *name);
char *get_env_value(t_shell *shell, char *name);
char **env_to_array(t_env *env);
int print_sorted_env(t_shell *shell, int out);
int len_2d_array(char **arr);
char *ft_strjoin3(char *s1, char *s2, char *s3);
void ft_exit_error(char *message, int status, t_shell *shell);
void ft_error(char *message);
void ft_error_concat(int count, ...);
void free_shell(t_shell *shell);
void free_token(t_token **token);
void free_split(char **split);

#endif