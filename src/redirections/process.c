/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:59:22 by csalazar          #+#    #+#             */
/*   Updated: 2025/04/26 15:46:02 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	set_fd(int temp, int fd, int fd_std, int hd)
{
	if (temp == -1)
		return (-1);
	if (fd != fd_std && fd != temp && fd != hd)
		close(fd);
	fd = temp;
	return (fd);
}

static int	here_doc_fail(char *err_msg)
{
	if (err_msg)
	{
		ft_putendl_fd(err_msg, 2);
		free(err_msg);
	}
	return (-1);
}

int process_here_doc_redir(t_token *token, t_shell *shell)
{
	int tmp;
	int hd;

	hd = STDIN_FILENO;
	while (token && token->type != PIPE)
	{
		if (token->type == HERE_DOC)
		{
			tmp = process_here_doc(token->data, shell);
			hd = set_fd(tmp, hd, STDIN_FILENO, -1);
			if (hd == -1)
				return (here_doc_fail(NULL));
		}
		token = token->next;
	}
	return (hd);
}

int	process_input_redirections(t_token *token, t_shell *shell, int com_count)
{
	int		in;
	int		tmp;
	char	*err_msg;

	err_msg = NULL;
	in = STDIN_FILENO;
	while (token && token->type != PIPE)
	{
		if (token->type == IN)
		{
			tmp = process_in(token->data, &err_msg);
			in = set_fd(tmp, in, STDIN_FILENO, shell->hd[com_count]);
		}
		else if (token->type == HERE_DOC)
		{
			tmp = shell->hd[com_count];
			in = set_fd(tmp, in, STDIN_FILENO, shell->hd[com_count]);
		}
/* 		{
			tmp = process_here_doc(token->data, shell);
			in = set_fd(tmp, in, STDIN_FILENO);
			if (in == -1)
				return (here_doc_fail(err_msg));
		} */
		token = token->next;
	}
	if (err_msg)
		return (ft_putendl_fd(err_msg, 2), free(err_msg), -1);
	return (in);
}

int	process_output_redirections(t_token *token)
{
	int		out;
	int		tmp;
	char	*err_msg;

	err_msg = NULL;
	out = STDOUT_FILENO;
	while (token && token->type != PIPE)
	{
		if (token->type == OUT)
		{
			tmp = process_out(token->data, &err_msg);
			out = set_fd(tmp, out, STDOUT_FILENO, -1);
		}
		else if (token->type == APPEND)
		{
			tmp = process_append(token->data, &err_msg);
			out = set_fd(tmp, out, STDOUT_FILENO, -1);
		}
		token = token->next;
	}
	if (err_msg)
		return (ft_putendl_fd(err_msg, 2), free(err_msg), -1);
	return (out);
}
