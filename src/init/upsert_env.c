/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upsert_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:24:16 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/08 08:03:01 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env	*append_env_var(t_shell *shell, char *name, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	if (!*(shell->env))
	{
		*(shell->env) = new;
		new->next = NULL;
	}
	else
	{
		tmp = *(shell->env);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
	new->name = name;
	new->value = value;
	return (new);
}

t_env *append_or_update(t_shell *shell, char *name, char *value)
{
	t_env *upsert;

	upsert = find_env_var_by_name(shell, name);
	if (upsert)
	{
		free(name);
		if (upsert->value)
			free(upsert->value);
		upsert->value = value;
	}
	else
		upsert = append_env_var(shell, name, value);
	if (!upsert)
	{
		//free(name);
		//free(value);
		return (NULL);
	}
	return (upsert);
}

int	upsert_env(t_shell *shell, char *envp)
{
	char	*name;
	char	*value;
	t_env	*upsert;

	if (!envp || !is_valid_env_var(envp))
		return (-1);
	if (!ft_strchr(envp, '='))
		return (0);
	name = ft_substr(envp, 0, ft_strchr(envp, '=') - envp);
	if (!name)
		return (ft_error(MALLOC_ERR), 0);
	value = ft_strdup(ft_strchr(envp, '=') + 1);
	if (!value)
	{
		free(name);
		return (ft_error(MALLOC_ERR), 0);
	}
	upsert = append_or_update(shell, name, value);
	if (!upsert)
		return (ft_error(MALLOC_ERR), 0);
	return (1);
}
