#include "../../include/minishell.h"

static void sort_env(char **env) {
    int count;
    int i;
    int j;
    char *temp;

    count = 0;
    i = 0;
    j = 0;
    while (env[count] != NULL)
        count++;
    i = 0;
    while (i < count - 1) {
        j = 0;
        while (j < count - i - 1) {
            if (ft_strcmp(env[j], env[j + 1]) > 0) 
            {
                temp = env[j];
                env[j] = env[j + 1];
                env[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
}

int print_sorted_env(t_shell *shell, int out)
{
    char **env;
    int i;
    
    env = env_to_array(*(shell->env));
    sort_env(env);
    i = 0;
    while (env[i])
    {
        ft_putstr_fd("declare -x ", out);
        ft_putendl_fd(env[i], out);
        i++;
    }
    free_split(env);
    return (0);
}
