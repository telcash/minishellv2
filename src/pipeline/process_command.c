#include "../../include/minishell.h"

int process_command(char **cmdargs, t_shell *shell, int i, t_io *io)
{
	pid_t pid;
	int code;

	if (cmdargs[0] && cmd_is_builtin(cmdargs[0]) && shell->pipes->nb_pipes == 0)
	{
		code = exec_built_in(shell, cmdargs, io->out);
		free(io);
		return code;
	}
	g_interactive = 0;
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		set_pipes(shell, io);
		free(io);
		if (!cmdargs[0])
			exit(0);
		if (cmd_is_builtin(cmdargs[0]))
			exit(exec_built_in(shell, cmdargs, STDOUT_FILENO));
		else
			exec_bin(shell, cmdargs);
	}
	else
	{
		shell->launched_procs++;
		shell->pids[i] = pid;
		free(io);
		return 0;
	}
	return 0;
}

t_io *get_io(t_token *segment, int com_count)
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
	return io;
}
