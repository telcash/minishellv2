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

# ifndef MALLOC_ERR_MSG
#  define MALLOC_ERR_MSG "Error: malloc failed"
# endif

typedef enum
{
    WORD,
	IN,
	HERE_DOC,
	OUT,
	APPEND,
	PIPE
}						t_token_type;

typedef struct s_io
{
    int					in;
    int				    out;
    int                 com_count;
}						t_io;

typedef struct s_fds
{
	int					**pipes;
	int					nb_pipes;
}						t_fds;

typedef struct s_token
{
    t_token_type    type;
    char            *data;
    struct s_token  *next;
}               t_token;

typedef struct s_env
{
    char            *name;
    char            *value;
    struct s_env    *next;
}   t_env;

typedef struct s_shell
{
    char        *path;
    char        *home;
    char        *oldpath;
    int         com_count;
    t_fds       *fds;      
    t_env       **env;
}               t_shell;

void            init_minishell(t_shell **shell, char **envp);
void            ft_error(char *message, int status, t_shell *shell);
void            free_shell(t_shell *shell);
void	        free_token(t_token **token);
t_token	        **get_token(char *line);
int             pipeline(t_token **token, t_shell *shell);
t_fds           *init_fds(t_token *token);
int             process_command(char **cmdargs, t_shell *shell, t_token *segment, int i);
int             ft_isspace(char c);
int             isseparator(char c);
void            append_token(t_token **token, char *data, t_token_type type);
char            *trim_quotes(char *word);
int             cmd_is_builtin(char *com);
int             exec_built_in(t_shell *minishell, char **cmdargs);
int             ft_pwd(t_shell *minishell);
int             ft_exit(t_shell *minishell, char **cmdargs);
int             process_output_redirections(t_token *token);
int             process_input_redirections(t_token *token);
void            free_split(char **split);
void            exec_bin(t_shell *minishell, char **cmdargs);
void            close_fds(t_fds *fds);
void            free_fds(t_fds *fds);
void            wait_all_childs(void);
int             process_out(char *file);
int             process_append(char *file);
int             process_in(char *file);

#endif