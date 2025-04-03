/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:07:37 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/03 10:45:04 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**get_cmdargs(t_token *token)
{
	int		i;
	char	**cmdargs;
	t_token	*tmp;

	i = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			i++;
		tmp = tmp->next;
	}
	cmdargs = ft_calloc(i + 1, sizeof(char *));
	if (!cmdargs)
		return (NULL);
	i = 0;
	tmp = token;
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
	t_token	*tmp;

	tmp = segment;
	while (tmp && tmp->type != PIPE)
		tmp = tmp->next;
	if (tmp)
		tmp = tmp->next;
	return (tmp);
}

int	pipeline(t_token **token, t_shell *shell)
{
	t_token	*segment;
	char	**cmdargs;
	int		i;

	i = 0;
	if (!token || !*token)
		return (0);
	segment = *token;
	shell->pipes = init_pipes(*token);
	shell->pids = ft_calloc(shell->pipes->nb_pipes + 1, sizeof(int));
	while (segment)
	{
		cmdargs = get_cmdargs(segment);
		if (!cmdargs)
			ft_error(MALLOC_ERR_MSG, 1, shell);
		process_command(cmdargs, shell, segment, i++);
		free(cmdargs);
		segment = get_next_segment(segment);
	}
	close_pipes(shell->pipes);
	free_pipes(shell->pipes);
	wait_all_childs(shell);
	shell->launched_procs = 0;
	free(shell->pids);
	return (0);
}
