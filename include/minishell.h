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

# ifndef INV_ARG_ERR
#  define INV_ARG_ERR "Error: invalid input"
# endif
# ifndef MALLOC_ERR
#  define MALLOC_ERR "Error: malloc failed"
# endif
# ifndef SIGINT_ERR
#  define SIGINT_ERR "ERROR registering SIGINT handler"
# endif
# ifndef SIGQUIT_ERR
#  define SIGQUIT_ERR "ERROR registering SIGQUIT handler"
# endif
# ifndef PATH_UPDATE_ERR
#  define PATH_UPDATE_ERR "Error updating the path"
# endif
# ifndef DIR_ACCESS_ERR
#  define DIR_ACCESS_ERR "Error accessing directory"
# endif
# ifndef NO_FILE_ERR
#  define NO_FILE_ERR "Error: no such file or directory"
# endif
# ifndef CD_TOO_MANY_ARGS_ERR
#  define CD_TOO_MANY_ARGS_ERR "minishell: cd: too many arguments"
# endif
# ifndef CD_NO_HOME_ERR
#  define CD_NO_HOME_ERR "minishell: cd: HOME not set"
# endif
# ifndef NO_PATH_ERR
#  define NO_PATH_ERR "Error getting the path"
# endif
# ifndef UN_TOKEN_NL_ERR
#  define UN_TOKEN_NL_ERR "minishell: syntax error near unexpected token `newline'"
# endif
# ifndef UN_TOKEN_PIPE_ERR
#  define UN_TOKEN_PIPE_ERR "minishell: syntax error near unexpected token `|'"
# endif
# ifndef UN_TOKEN_2PIPE_ERR
#  define UN_TOKEN_2PIPE_ERR "minishell: syntax error near unexpected token `||'"
# endif

extern int			g_interactive;

typedef enum
{
	WORD,
	IN,
	HERE_DOC,
	OUT,
	APPEND,
	PIPE
}					t_token_type;

typedef struct s_io
{
	int				in;
	int				out;
	int				com_count;
}					t_io;

typedef struct s_pipe
{
	int				**pipes;
	int				nb_pipes;
}					t_pipe;

typedef struct s_token
{
	t_token_type	type;
	char			*data;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	char			*path;
	char			*oldpath;
	int				com_count;
	int				last_exit_status;
	int				*pids;
	int				launched_procs;
	t_pipe			*pipes;
	t_token			**token;
	t_env			**env;
}					t_shell;

void				init_minishell(t_shell **shell, char **envp);
void				ft_exit_error(char *message, int status, t_shell *shell);
void				ft_error(char *message);
void				ft_error_concat(int count, ...);
void				free_shell(t_shell *shell);
void				free_token(t_token **token);
void				get_token(char *line, t_shell *shell);
int					pipeline(t_shell *shell);
t_pipe				*init_pipes(t_token *token);
int					process_command(char **cmdargs, t_shell *shell,
						t_token *segment, int i);
int					ft_isspace(char c);
int					isseparator(char c);
void				append_token(char *data, t_token_type type,
						t_shell *shell);
char				*trim_quotes(char *word);
int					cmd_is_builtin(char *com);
int					exec_built_in(t_shell *minishell, char **cmdargs, int out);
int					ft_pwd(t_shell *minishell, int out);
int					ft_exit(t_shell *minishell, char **cmdargs);
int					ft_cd(t_shell *minishell, char **cmdargs);
int					ft_echo(char **cmdargs, int out);
int					ft_env(t_shell *minishell, int out);
int					ft_export(t_shell *minishell, char **cmdargs);
int					ft_unset(t_shell *minishell, char **cmdargs);
int					process_output_redirections(t_token *token);
int					process_input_redirections(t_token *token);
int					process_here_doc(char *delimiter);
void				free_split(char **split);
void				exec_bin(t_shell *minishell, char **cmdargs);
void				close_pipes(t_pipe *pipes);
void				free_pipes(t_pipe *pipes);
int					process_out(char *file);
int					process_append(char *file);
int					process_in(char *file);
void				set_pipes(t_shell *shell, t_io *io);
int					upsert_env(t_shell *shell, char *envp);
int					is_valid_env_var(char *str);
t_env				*find_env_var_by_name(t_shell *shell, char *name);
char				*expand_variable(char *data, t_shell *shell);
void				set_signal(void);
char				*get_env_value(t_shell *shell, char *name);
int					verify_token(t_token **token);
char 				*ft_strjoin3(char *s1, char *s2, char *s3);
int					len_2d_array(char **arr);
int 				print_sorted_env(t_shell *shell);

#endif