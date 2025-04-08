/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfernan3 <dfernan3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:05:29 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/08 15:50:15 by dfernan3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_env(t_shell *shell, char **envp)
{
	int	i;

	if (!envp || !*envp)
	{
		(*shell->env = NULL);
		return ;
	}
	shell->env = malloc(sizeof(t_env *));
	if (!shell->env)
		ft_exit_error(MALLOC_ERR, EXIT_FAILURE, shell);
	i = 0;
	(*shell->env) = NULL;
	while (envp[i])
		upsert_env(shell, envp[i++]);
	append_or_update(shell, ft_strdup("PWD"), getcwd(NULL, 0));
}

char	*get_env_value(t_shell *shell, char *name)
{
	t_env	*tmp;

	tmp = find_env_var_by_name(shell, name);
	if (!tmp || !tmp->value)
		return (NULL);
	return (tmp->value);
}

t_env	*find_env_var_by_name(t_shell *shell, char *name)
{
	t_env	*tmp;

	if (!name)
		return (NULL);
	tmp = *(shell->env);
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
	(*shell)->pwd = getcwd(NULL, 0);
	(*shell)->oldpwd = NULL;
	(*shell)->pipes = NULL;
	(*shell)->last_exit_status = 0;
	(*shell)->launched_procs = 0;
	(*shell)->token = NULL;
	init_env(*shell, envp);
}
