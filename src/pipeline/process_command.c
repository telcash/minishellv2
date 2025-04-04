/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:20:50 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/04 09:41:33 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_io *get_io(t_token *segment, int com_count)
{
    t_io *io;

    io = ft_calloc(1, sizeof(t_io));
    if (!io)
        ft_exit_error(MALLOC_ERR, 1, NULL);
    io->in = process_input_redirections(segment);
	if (io->in == -1)
		io->out = STDOUT_FILENO;
	else
    	io->out = process_output_redirections(segment);
    io->com_count = com_count;
    return (io);
}

static int exec_built_in_alone(t_shell *shell, char **cmdargs, t_token *segment)
{
	t_io	*io;
	int		code;

	io = get_io(segment, 0);
	if (io->in == -1)
	{
		free(io);
		return (1);
	}
	code = exec_built_in(shell, cmdargs, io->out);
	free(io);
	return (code);
}

int process_command(char **cmdargs, t_shell *shell, t_token *segment, int i)
{
	pid_t		pid;
	t_io	*io;

	if (cmdargs[0] && cmd_is_builtin(cmdargs[0]) && shell->pipes->nb_pipes == 0)
		return (exec_built_in_alone(shell, cmdargs, segment));
	g_interactive = 0;
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		io = get_io(segment, i);
		set_pipes(shell, io);
 		if (io->in == -1)
		{
			free(io);
			exit (1);
		}
		free(io);
		if (cmdargs == NULL || cmdargs[0] == NULL)
			exit (0);
		if (cmd_is_builtin(cmdargs[0]))
			return (exec_built_in(shell, cmdargs, STDOUT_FILENO));
		else
			exec_bin(shell, cmdargs);
	}
	else
	{
		shell->launched_procs++;
		shell->pids[i] = pid;
		return (0);
	}
	return (0);
}
