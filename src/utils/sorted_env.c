#include "../../include/minishell.h"

void sort_env(t_env **env)
{
    int ordered;
    t_env *tmp;
    t_env *next_node;
    char *tmp_name;
    char *tmp_value;

    if (!env || !*env)
        return;
    ordered = 0;
    while (!ordered)
    {
        ordered = 1;
        tmp = *env;
        while (tmp && tmp->next)
        {
            next_node = tmp->next;
            if (ft_strcmp(tmp->name, next_node->name) > 0)
            {
                tmp_name = tmp->name;
                tmp_value = tmp->value;
                tmp->name = next_node->name;
                tmp->value = next_node->value;
                next_node->name = tmp_name;
                next_node->value = tmp_value;
                ordered = 0;
            }
            tmp = tmp->next;
        }
    }
}

int print_sorted_env(t_shell *shell)
{
    t_env *env;
    
    env = *shell->env;
    sort_env(&env);
    while (env)
    {
        printf("declare -x ");
        printf("%s=%s\n", env->name, env->value);
        env = env->next;
    }
    return (0);
}
