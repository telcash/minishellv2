/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upsert_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:24:16 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/04 09:46:27 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env	*append_env_var(t_shell *shell)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		ft_exit_error(MALLOC_ERR, 1, shell);
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

int	upsert_env(t_shell *shell, char *envp)
{
	t_env	*upsert;
	char	*name;
	char	*value;
	char	*equal_sign;

	if (!envp || !is_valid_env_var(envp))
		return (-1);
	equal_sign = ft_strchr(envp, '=');
	if (!equal_sign)
		return (0);
	name = ft_substr(envp, 0, equal_sign - envp);
	value = ft_strdup(equal_sign + 1);
	if (!name || !value)
		ft_exit_error(MALLOC_ERR, 1, shell);
	upsert = find_env_var_by_name(shell, name);
	if (!upsert)
		upsert = append_env_var(shell);
	upsert->name = name;
	upsert->value = value;
	return (1);
}
