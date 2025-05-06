/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:07:56 by csalazar          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/22 20:09:27 by csalazar         ###   ########.fr       */
=======
/*   Updated: 2025/05/06 13:39:24 by csalazar         ###   ########.fr       */
>>>>>>> redir
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

<<<<<<< HEAD
static int	process_built_in_alone(t_shell *shell, char **cmdargs, t_token *segment)
{
	int	code;
	t_io *io;

	io = get_io(segment, 0, shell);
=======
static int	process_built_in_alone(t_shell *shell, char **cmdargs,
		t_token *segment, int i)
{
	int		code;
	t_io	*io;

	io = get_io(segment, i, shell);
>>>>>>> redir
	code = exec_built_in(shell, cmdargs, io);
	if (io)
	{
		if (io->in != STDIN_FILENO)
			close(io->in);
		if (io->out != STDOUT_FILENO)
			close(io->out);	
		free(io);
	}
	return (code);
}

static int	father_process_clean(t_shell *shell, pid_t pid, int i)
{
	shell->launched_procs++;
	shell->pids[i] = pid;
<<<<<<< HEAD
/* 	if (io->in != STDIN_FILENO)
		close(io->in);
	if (io->out != STDOUT_FILENO)
		close(io->out);
	free(io); */
=======
	if (shell->hd[i] != -1 && shell->hd[i] != STDIN_FILENO)
		close(shell->hd[i]);
>>>>>>> redir
	return (0);
}

t_io	*get_io(t_token *segment, int com_count, t_shell *shell)
{
	t_io	*io;

	io = ft_calloc(1, sizeof(t_io));
	if (!io)
		ft_exit_error(MALLOC_ERR, 1, NULL);
	io->in = process_input_redirections(segment, shell, com_count);
	if (io->in == -1)
		io->out = STDOUT_FILENO;
	else
		io->out = process_output_redirections(segment);
	io->com_count = com_count;
	return (io);
}

<<<<<<< HEAD
static void	process_child(t_shell *shell, char **cmdargs, t_token *segment, int i)
{
	t_io *io;
=======
static void	process_child(t_shell *shell, t_token *segment, int i,
		char **cmdargs)
{
	t_io	*io;
>>>>>>> redir

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	io = get_io(segment, i, shell);
	set_pipes(shell, io);
	if (io->in == -1 || io->out == -1)
	{
		if (io->in != STDIN_FILENO)
			close(io->in);
		if (io->out != STDOUT_FILENO)
			close(io->out);
		free(io);
		exit(1);
	}
	if (io->in != STDIN_FILENO)
		close(io->in);
	if (io->out != STDOUT_FILENO)
		close(io->out);
	free(io);
	if (!cmdargs[0])
		exit(0);
	if (cmd_is_builtin(cmdargs[0]))
		exit(exec_built_in(shell, cmdargs, NULL));
	exec_bin(shell, cmdargs);
}

int	process_command(char **cmdargs, t_shell *shell, int i, t_token *segment)
{
	pid_t	pid;

	if (shell->pipes->nb_pipes == 0 && cmdargs && cmdargs[0])
	{
		if (shell->_)
			free(shell->_);
		shell->_ = ft_strdup(get_last_cmdarg(cmdargs));
	}
	if (cmdargs[0] && cmd_is_builtin(cmdargs[0]) && shell->pipes->nb_pipes == 0)
<<<<<<< HEAD
		return (process_built_in_alone(shell, cmdargs, segment));
=======
		return (process_built_in_alone(shell, cmdargs, segment, i));
>>>>>>> redir
	g_interactive = NON_INTERACTIVE;
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
<<<<<<< HEAD
		process_child(shell, cmdargs, segment, i);
=======
		process_child(shell, segment, i, cmdargs);
>>>>>>> redir
	else
		return (father_process_clean(shell, pid, i));
	return (0);
}
