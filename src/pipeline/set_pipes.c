/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:22:53 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/01 18:19:01 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	set_first_pipe(t_shell *shell, t_io *io)
{
	if (io->in != STDIN_FILENO)
		dup2(io->in, STDIN_FILENO);
	if (io->out != STDOUT_FILENO)
		dup2(io->out, STDOUT_FILENO);
	else
		dup2(shell->pipes->pipes[io->com_count][1], STDOUT_FILENO);
}

static void	set_last_pipe(t_shell *shell, t_io *io)
{
	if (io->in != STDIN_FILENO)
		dup2(io->in, STDIN_FILENO);
	else
		dup2(shell->pipes->pipes[io->com_count - 1][0], STDIN_FILENO);
	if (io->out != STDOUT_FILENO)
		dup2(io->out, STDOUT_FILENO);
}

static void	set_middle_pipe(t_shell *shell, t_io *io)
{
	if (io->in != STDIN_FILENO)
		dup2(io->in, STDIN_FILENO);
	else
		dup2(shell->pipes->pipes[io->com_count - 1][0], STDIN_FILENO);
	if (io->out != STDOUT_FILENO)
		dup2(io->out, STDOUT_FILENO);
	else
		dup2(shell->pipes->pipes[io->com_count][1], STDOUT_FILENO);
}

void	set_pipes(t_shell *shell, t_io *io)
{
	if (shell->pipes->nb_pipes > 0)
	{
		if (io->com_count == 0)
			set_first_pipe(shell, io);
		else if (io->com_count == shell->pipes->nb_pipes)
			set_last_pipe(shell, io);
		else
			set_middle_pipe(shell, io);
	}
	else
	{
		if (io->in != STDIN_FILENO)
			dup2(io->in, STDIN_FILENO);
		if (io->out != STDOUT_FILENO)
			dup2(io->out, STDOUT_FILENO);
	}
	if (io->in != STDIN_FILENO)
		close(io->in);
	if (io->out != STDOUT_FILENO)
		close(io->out);
	close_pipes(shell->pipes);
}