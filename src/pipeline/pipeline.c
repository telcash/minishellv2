/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:07:37 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/26 22:41:24 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**get_cmdargs(t_token *token)
{
	int		i;
	char	**cmdargs;
	t_token	*tmp;

	i = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			i++;
		tmp = tmp->next;
	}
	cmdargs = ft_calloc(i + 1, sizeof(char *));
	if (!cmdargs)
		return (NULL);
	i = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			cmdargs[i++] = tmp->data;
		tmp = tmp->next;
	}
	return (cmdargs);
}

static t_token *get_next_segment(t_token *segment)
{
    t_token *tmp;

    tmp = segment;
    while (tmp && tmp->type != PIPE)
        tmp = tmp->next;
    if (tmp)
        tmp = tmp->next;
    return (tmp);
}

int pipeline(t_token **token, t_shell *shell)
{
    t_token *segment;
    char **cmdargs;
    int i;

    i = 0;
    segment = *token;
    shell->fds = init_fds(*token);
    while (segment)
    {
        cmdargs = get_cmdargs(segment);
        if (!cmdargs)
            ft_error(MALLOC_ERR_MSG, 1, shell);
        process_command(cmdargs, shell, segment, i++);
        free(cmdargs);
        segment = get_next_segment(segment);
    }
    close_fds(shell->fds);
    free_fds(shell->fds);
    wait_all_childs();
    return (0);
}
