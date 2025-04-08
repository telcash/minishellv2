/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:45:23 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/07 20:44:43 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void remove_env_var(t_env **env, char *name)
{
	t_env *prev;
	t_env *curr;

	prev = NULL;
	curr = *env;
	while (curr)
	{
		if (ft_strcmp(curr->name, name) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->name);
			free(curr->value);
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	ft_unset(t_shell *shell, char **cmdargs)
{
	int i;

	i = 1;
	while (cmdargs[i])
	{
		if (is_valid_env_var(cmdargs[i]))
			remove_env_var(shell->env, cmdargs[i]);
		i++;
	}
	return (0);
}