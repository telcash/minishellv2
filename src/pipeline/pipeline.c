/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:07:27 by csalazar          #+#    #+#             */
/*   Updated: 2025/04/24 18:39:51 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	wait_all_childs(t_shell *shell)
{
	pid_t	pid;
	int		status;
	int		i;
	int		sig;

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
				shell->last_exit_status = 128 + sig;
				if (sig == 3)
					ft_putendl_fd("Quit (core dumped)", 2);
			}
		}
		i++;
	}
}

static char	**get_cmdargs(t_token *token)
{
	int		i;
	t_token	*tmp;
	char	**cmdargs;

	tmp = token;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			i++;
		tmp = tmp->next;
	}
	cmdargs = ft_calloc(i + 1, sizeof(char *));
	if (!cmdargs)
		return (NULL);
	tmp = token;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			cmdargs[i++] = tmp->data;
		tmp = tmp->next;
	}
	return (cmdargs);
}

static t_token	*get_next_segment(t_token *segment)
{
	while (segment && segment->type != PIPE)
		segment = segment->next;
	if (segment)
		return (segment->next);
	return (NULL);
}

static void	process_tokens(t_token *segment, t_shell *shell)
{
	int		i;
	char	**cmdargs;
	t_token *tmp;
	//t_io	*io;
	//int hd;

	i = 0;
	shell->hd = malloc(sizeof(int) * 1024);
	tmp = segment;
	while (tmp)
	{
		shell->hd[i] = process_here_doc_redir(tmp, shell);
		if (shell->hd[i] == -1)
			return ;
		i++;
		tmp = get_next_segment(tmp);
	}
	i = 0;
	while (segment)
	{
		cmdargs = get_cmdargs(segment);
		//shell->hd = process_here_doc_redir(segment, shell);
		//io = get_io(segment, i, shell);
		process_command(cmdargs, shell, i++, segment);
		free(cmdargs);
		segment = get_next_segment(segment);
		//shell->hd = STDIN_FILENO;
	}
	free(shell->hd);
}

int	pipeline(t_shell *shell)
{
	if (!shell->token || !*(shell->token))
		return (0);
	shell->pipes = init_pipes(*(shell->token));
	shell->pids = ft_calloc(shell->pipes->nb_pipes + 1, sizeof(int));
	process_tokens(*(shell->token), shell);
	close_pipes(shell->pipes);
	free_pipes(shell->pipes);
	wait_all_childs(shell);
	shell->launched_procs = 0;
	free(shell->pids);
	return (0);
}
