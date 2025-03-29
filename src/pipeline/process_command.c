/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:20:50 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/29 10:29:12 by carlossalaz      ###   ########.fr       */
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

static int exec_built_in_alone(t_shell *shell, char **cmdargs, t_token *segment)
{
	t_io	*io;
	int		code;

	io = get_io(segment, 0);
	if (io->in == -1)
	{
		free(io);
		return (-1);
	}
	code = exec_built_in(shell, cmdargs, io->out);
	free(io);
	return (code);
}

int process_command(char **cmdargs, t_shell *shell, t_token *segment, int i)
{
	int		pid;
	t_io	*io;

	if (cmd_is_builtin(cmdargs[0]) && shell->pipes->nb_pipes == 0)
		return (exec_built_in_alone(shell, cmdargs, segment));
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		io = get_io(segment, i);
		set_pipes(shell, io);
		if (io->in == -1)
			exit (1);
		free(io);
		if (cmd_is_builtin(cmdargs[0]))
			return (exec_built_in(shell, cmdargs, STDOUT_FILENO));
		else
			exec_bin(shell, cmdargs);
	}
	return (0);
}
