/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:24:50 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/19 09:30:22 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void free_env(t_env **env)
{
    t_env *tmp;

    while (*env)
	{
		if ((*env)->name)
			free((*env)->name);
		if ((*env)->value)
			free((*env)->value);
		tmp = *env;
		*env = (*env)->next;
		free(tmp);
	}
	free(env);
}

void free_shell(t_shell *shell)
{
    if (!shell)
        return ;
    if (shell->env)
        free_env(shell->env);
    free(shell);
}
