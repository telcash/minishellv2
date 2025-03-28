/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:24:50 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/26 20:03:31 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void close_fds(t_fds *fds)
{
	int i;

	i = 0;
	while (i < fds->nb_pipes)
	{
		close(fds->pipes[i][0]);
		close(fds->pipes[i][1]);
		i++;
	}
}

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

void	free_token(t_token **token)
{
	t_token	*tmp;

	if (!token || !*token)
		return ;
	while (*token)
	{
		if ((*token)->data)
			free((*token)->data);
		tmp = *token;
		*token = (*token)->next;
		free(tmp);
	}
	free(token);
}

void free_split(char **split)
{
    int i;

    i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

void free_fds(t_fds *fds)
{
	int i;

	i = 0;
	while (i < fds->nb_pipes)
	{
		free(fds->pipes[i]);
		i++;
	}
	free(fds->pipes);
	free(fds);
}

void wait_all_childs(void)
{
    int pid;

    pid = wait(NULL);
    while (pid > 0)
        pid = wait(NULL);
}