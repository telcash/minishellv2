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

typedef struct s_token
{
    t_token_type    type;
    char            *data;
    struct s_token  *next;
}               t_token;

typedef struct s_cmd
{
    char            **cmds;
    t_token         *inredirs;
    t_token         *outredirs;
}               t_cmd;

typedef struct s_env
{
    char            *name;
    char            *value;
    struct s_env    *next;
}   t_env;

typedef struct s_shell
{
    t_env       **env;
}               t_shell;

void            init_minishell(t_shell **shell, char **envp);
void            ft_error(char *message, int status, t_shell *shell);
void            free_shell(t_shell *shell);

#endif