#include "../../include/minishell.h"

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
			if (tmp == -1)
				return -1;
			if (in != STDIN_FILENO)
				close(in);
			in = tmp;
		}
		else if (token->type == HERE_DOC)
		{
			tmp = process_here_doc(token->data);
			if (tmp == -1)
				return -1;
			if (in != STDIN_FILENO)
				close(in);
			in = tmp;
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
			if (tmp == -1)
				return -1;
			if (out != STDOUT_FILENO)
				close(out);
			out = tmp;
		}
		else if (token->type == APPEND)
		{
			tmp = process_append(token->data);
			if (tmp == -1)
				return -1;
			if (out != STDOUT_FILENO)
				close(out);
			out = tmp;
		}
		token = token->next;
	}
	return out;
}
