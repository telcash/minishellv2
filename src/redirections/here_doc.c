/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:08:37 by csalazar          #+#    #+#             */
/*   Updated: 2025/04/11 11:38:06 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	run_here_doc_loop(int write_fd, char *delimiter)
{
	char	*line;
	size_t	len;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, len);
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
}

static void	run_here_doc(int *fd, char *delimiter)
{
	signal(SIGINT, SIG_DFL);
	close(fd[0]);
	run_here_doc_loop(fd[1], delimiter);
	exit(EXIT_SUCCESS);
}

int	process_here_doc(char *delimiter)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
		run_here_doc(fd, delimiter);
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		close(fd[0]);
		g_interactive = NON_INTERACTIVE;
		return (-1);
	}
	return (fd[0]);
}
