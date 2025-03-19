/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:05:29 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/19 10:59:17 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env *append_env_var(t_shell *shell)
{
    t_env *new;
    t_env *tmp;

    new = malloc(sizeof(t_env));
    if (!new)
        ft_error(MALLOC_ERR_MSG, 1, shell);
    if (!*(shell->env))
    {
        *(shell->env) = new;
        new->next = NULL;
        return (new);
    }
    tmp = *(shell->env);
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    new->next = NULL;
    return (new);    
}

static t_env *find_env_var_by_name(t_shell *shell, char *name)
{
    t_env *tmp;

    tmp = *(shell->env);
    while (tmp && tmp->name)
    {
        if (ft_strcmp(tmp->name, name) == 0)
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}

static int is_valid_env_var(char *str)
{
	int i;

	i = 0;
	if (!str || !(ft_isalpha(str[i]) || str[i] == '_'))
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static void upsert_env(t_shell *shell, char *envp)
{
    t_env *upsert;
    char *name;
    char *value;
    char *equal_sign;

    if (!envp || !is_valid_env_var(envp))
        return ;
    equal_sign = ft_strchr(envp, '=');
    name = ft_substr(envp, 0, equal_sign - envp);
    value = ft_strdup(equal_sign + 1);
    if (!name || !value)
        ft_error(MALLOC_ERR_MSG, 1, shell);
    upsert = find_env_var_by_name(shell, name);
    if (!upsert)
        upsert = append_env_var(shell);
    upsert->name = name;
    upsert->value = value;
}

static void init_env(t_shell *shell, char **envp)
{
    int i;

    if(!envp || !*envp)
        return ;
    shell->env = malloc(sizeof(t_env *));
    if (!shell->env)
        ft_error(MALLOC_ERR_MSG, 1, shell);
    i = 0;
    (*shell->env) = NULL;
    while(envp[i])
        upsert_env(shell, envp[i++]);
}

void    init_minishell(t_shell **shell, char **envp)
{
    *shell = malloc(sizeof(t_shell));
    if (!*shell)
        ft_error(MALLOC_ERR_MSG, 1, NULL);
    init_env(*shell, envp);
}
