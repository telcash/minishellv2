#include "../../include/minishell.h"

int process_here_doc(char *delimiter)
{
	int fd[2];
	char *line;
	size_t len;

	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	return (close(fd[1]), fd[0]);
}
