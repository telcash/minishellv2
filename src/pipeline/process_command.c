/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:20:50 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/26 22:42:35 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_io *get_io(t_token *segment, int com_count)
{
    t_io *io;

    io = ft_calloc(1, sizeof(t_io));
    if (!io)
        ft_error(MALLOC_ERR_MSG, 1, NULL);
    io->in = process_input_redirections(segment);
    io->out = process_output_redirections(segment);
    io->com_count = com_count;
    return (io);
}

static void set_pipes(t_shell *shell, t_io *io)
{
	if (shell->fds->nb_pipes > 0)
	{
		if (io->com_count == 0)
		{
			if (io->in != STDIN_FILENO)
				dup2(io->in, STDIN_FILENO);
			if (io->out != STDOUT_FILENO)
				dup2(io->out, STDOUT_FILENO);
			else
				dup2(shell->fds->pipes[io->com_count][1], STDOUT_FILENO);

		}
		else if (io->com_count == shell->fds->nb_pipes)
		{
			if (io->in != STDIN_FILENO)
				dup2(io->in, STDIN_FILENO);
			else
				dup2(shell->fds->pipes[io->com_count - 1][0], STDIN_FILENO);
			if (io->out != STDOUT_FILENO)
				dup2(io->out, STDOUT_FILENO);
		}
		else
		{
			if (io->in != STDIN_FILENO)
				dup2(io->in, STDIN_FILENO);
			else
				dup2(shell->fds->pipes[io->com_count - 1][0], STDIN_FILENO);
			if (io->out != STDOUT_FILENO)
				dup2(io->out, STDOUT_FILENO);
			else
				dup2(shell->fds->pipes[io->com_count][1], STDOUT_FILENO);
		}
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
	close_fds(shell->fds);
}

static int exec_built_in_alone(t_shell *shell, char **cmdargs)
{
	return (exec_built_in(shell, cmdargs));
}

int process_command(char **cmdargs, t_shell *shell, t_token *segment, int i)
{
	int		pid;
	t_io	*io;

	if (cmd_is_builtin(cmdargs[0]) && shell->fds->nb_pipes == 0)
		return (exec_built_in_alone(shell, cmdargs));
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		io = get_io(segment, i);
		set_pipes(shell, io);
		free(io);
		if (cmd_is_builtin(cmdargs[0]))
			return (exec_built_in(shell, cmdargs));
		else
			exec_bin(shell, cmdargs);
	}
	return (0);
}
