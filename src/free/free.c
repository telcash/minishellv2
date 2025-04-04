/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:24:50 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/04 10:06:45 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_pipes(t_pipe *pipes)
{
	int	i;

	i = 0;
	while (i < pipes->nb_pipes)
	{
		close(pipes->pipes[i][0]);
		close(pipes->pipes[i][1]);
		i++;
	}
}

static void	free_env(t_env **env)
{
	t_env	*tmp;

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

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->env)
		free_env(shell->env);
	if (shell->path)
		free(shell->path);
	if (shell->oldpath)
		free(shell->oldpath);
	if (shell->token)
		free_token(shell->token);
	if (shell->pipes)
		free_pipes(shell->pipes);
	if (shell->pids)
		free(shell->pids);
	free(shell);
}

void	free_token(t_token **token)
{
	t_token	*tmp;

	if (!token)
		return ;
	if (!*token)
	{
		free (token);
		return ;
	}
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

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_pipes(t_pipe *pipes)
{
	int	i;

	i = 0;
	while (i < pipes->nb_pipes)
	{
		free(pipes->pipes[i]);
		i++;
	}
	free(pipes->pipes);
	free(pipes);
}

void	wait_all_childs(t_shell *shell)
{
	pid_t pid;
	int status;
	int i;
	int sig;

	i = 0;
	while (i < shell->launched_procs)
	{
		pid = wait(&status);
		if (pid == shell->pids[shell->launched_procs - 1])
		{
			if ((status & 0x7F) == 0)
				shell->last_exit_status = (status >> 8) & 0xFF;
			else
			{
				sig = status & 0x7F;
				shell->last_exit_status = 128 + (status & 0x7F);
				if (sig == 3)
					ft_putendl_fd("Quit (core dumped)", 2);
			}
		}
		i++;
	}
}
