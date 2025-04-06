#include "../../include/minishell.h"

static int set_fd(int temp, int fd, int fd_std)
{
	if (temp == -1)
		return (-1);
	if (fd != fd_std)
		close(fd);
	fd = temp;
	return fd;
}

int process_input_redirections(t_token *token)
{
	int in;
	int tmp;
	
	in = STDIN_FILENO;
	while (token && token->type != PIPE)
	{
		if (token->type == IN)
		{
			tmp = process_in(token->data);
			in = set_fd(tmp, in, STDIN_FILENO);
			if (in == -1)
				return -1;
		}
		else if (token->type == HERE_DOC)
		{
			tmp = process_here_doc(token->data);
			in = set_fd(tmp, in, STDIN_FILENO);
			if (in == -1)
				return -1;
		}
		token = token->next;
	}
	return in;
}

int process_output_redirections(t_token *token)
{
	int out;
	int tmp;
	
	out = STDOUT_FILENO;
	while (token && token->type != PIPE)
	{
		if (token->type == OUT)
		{
			tmp = process_out(token->data);
			out = set_fd(tmp, out, STDOUT_FILENO);
			if (out == -1)
				return -1;
		}
		else if (token->type == APPEND)
		{
			tmp = process_append(token->data);
			out = set_fd(tmp, out, STDOUT_FILENO);
			if (out == -1)
				return -1;
		}
		token = token->next;
	}
	return out;
}
