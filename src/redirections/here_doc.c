/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:08:37 by csalazar          #+#    #+#             */
/*   Updated: 2025/04/15 20:41:45 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	run_here_doc_loop(int write_fd, char *delimiter, int has_quotes,
		t_shell *shell)
{
	char	*line;
	size_t	len;
	char	*expanded_line;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		expanded_line = expand_here_doc(line, has_quotes, shell);
		free(line);
		len = ft_strlen(expanded_line);
		if (len > 0 && expanded_line[len - 1] == '\n')
			expanded_line[len - 1] = '\0';
		if (ft_strcmp(expanded_line, delimiter) == 0)
		{
			free(expanded_line);
			break ;
		}
		write(write_fd, expanded_line, len);
		write(write_fd, "\n", 1);
		free(expanded_line);
	}
	close(write_fd);
}

static void	run_here_doc(int *fd, char *delimiter, t_shell *shell)
{
	char	*trimmed_delimiter;
	int		has_quotes;

	has_quotes = 0;
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'))
		has_quotes = 1;
	trimmed_delimiter = trim_line_quotes(delimiter);
	free(delimiter);
	signal(SIGINT, SIG_DFL);
	close(fd[0]);
	run_here_doc_loop(fd[1], trimmed_delimiter, has_quotes, shell);
	exit(EXIT_SUCCESS);
}

int	process_here_doc(char *delimiter, t_shell *shell)
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
		run_here_doc(fd, delimiter, shell);
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
