/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:59:22 by csalazar          #+#    #+#             */
/*   Updated: 2025/04/12 13:38:00 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	set_fd(int temp, int fd, int fd_std)
{
	if (temp == -1)
		return (-1);
	if (fd != fd_std)
		close(fd);
	fd = temp;
	return (fd);
}

int	process_input_redirections(t_token *token)
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
			in = set_fd(tmp, in, STDIN_FILENO);
		}
		else if (token->type == HERE_DOC)
		{
			tmp = process_here_doc(token->data);
			in = set_fd(tmp, in, STDIN_FILENO);
			if (in == -1 && err_msg)
				return (ft_putendl_fd(err_msg, 2), free(err_msg), -1);
			else if (in == -1)
				return (-1);
		}
		token = token->next;
	}
	if (err_msg)
		return (ft_putendl_fd(err_msg, 2), free(err_msg), -1);
	return (in);
}

int	process_output_redirections(t_token *token)
{
	int	out;
	int	tmp;
	char *err_msg;

	err_msg = NULL;
	out = STDOUT_FILENO;
	while (token && token->type != PIPE)
	{
		if (token->type == OUT)
		{
			tmp = process_out(token->data, &err_msg);
			out = set_fd(tmp, out, STDOUT_FILENO);
		}
		else if (token->type == APPEND)
		{
			tmp = process_append(token->data, &err_msg);
			out = set_fd(tmp, out, STDOUT_FILENO);
		}
		token = token->next;
	}
	if (err_msg)
		return (ft_putendl_fd(err_msg, 2), free(err_msg), -1);
	return (out);
}
