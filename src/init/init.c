/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:05:29 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/12 16:40:55 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void update_shlvl(t_shell *shell)
{
	char *level;
	int new_level;
	char *new_level_str;

	level = get_env_value(shell->env, "SHLVL");
	if (level)
	{
		new_level = ft_atoi(level) + 1;
		new_level_str = ft_itoa(new_level);
		append_or_update(shell->env, ft_strdup("SHLVL"), new_level_str);
		append_or_update(shell->export, ft_strdup("SHLVL"), new_level_str);
	}
}

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
	*(shell->env) = NULL;
	*(shell->export) = NULL;
	i = -1;
	while (envp[++i])
	{
		upsert_env(shell->env, envp[i]);
		upsert_env(shell->export, envp[i]);
	}
	append_or_update(shell->env, ft_strdup("PWD"), getcwd(NULL, 0));
	append_or_update(shell->export, ft_strdup("PWD"), getcwd(NULL, 0));
	update_shlvl(shell);
}

char	*get_env_value(t_env **env, char *name)
{
	t_env	*tmp;

	tmp = find_env_var_by_name(env, name);
	if (!tmp || !tmp->value)
		return (NULL);
	return (tmp->value);
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
