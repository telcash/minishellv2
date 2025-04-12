/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:05:29 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/12 15:23:48 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_env(t_shell *shell, char **envp)
{
	int	i;

	if (!envp || !*envp)
	{
		shell->env = NULL;
		shell->export = NULL;
		return ;
	}
	shell->env = malloc(sizeof(t_env *));
	if (!shell->env)
		ft_exit_error(MALLOC_ERR, EXIT_FAILURE, shell);
	shell->export = malloc(sizeof(t_env *));
	if (!shell->export)
		ft_exit_error(MALLOC_ERR, EXIT_FAILURE, shell);
	i = 0;
	*(shell->env) = NULL;
	*(shell->export) = NULL;
	while (envp[i])
	{
		upsert_env(shell->env, envp[i]);
		upsert_env(shell->export, envp[i]);
		i++;
	}
	append_or_update(shell->env, ft_strdup("PWD"), getcwd(NULL, 0));
}

char	*get_env_value(t_env **env, char *name)
{
	t_env	*tmp;

	tmp = find_env_var_by_name(env, name);
	if (!tmp || !tmp->value)
		return (NULL);
	return (tmp->value);
}

t_env	*find_env_var_by_name(t_env **env, char *name)
{
	t_env	*tmp;

	if (!name)
		return (NULL);
	tmp = *env;
	while (tmp && tmp->name)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	is_valid_env_var(char *str)
{
	int	i;

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

void	init_minishell(t_shell **shell, char **envp)
{
	*shell = malloc(sizeof(t_shell));
	if (!*shell)
		ft_exit_error(MALLOC_ERR, EXIT_FAILURE, NULL);
	(*shell)->last_exit_status = 0;
	(*shell)->launched_procs = 0;
	(*shell)->oldpwd = NULL;
	(*shell)->pipes = NULL;
	(*shell)->token = NULL;
	(*shell)->pids = NULL;
	init_env(*shell, envp);
	(*shell)->pwd = getcwd(NULL, 0);
	if (!(*shell)->pwd)
	{
		ft_error_concat(2, "minishell-init: ", CWD_ERR);
		free_shell(*shell);
		exit(EXIT_FAILURE);
	}
}
