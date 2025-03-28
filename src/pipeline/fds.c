/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:14:50 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/26 13:37:01 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int get_number_of_pipes(t_token *token)
{
	int		nb_pipes;
	t_token	*tmp;

	nb_pipes = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == PIPE)
			nb_pipes++;
		tmp = tmp->next;
	}
	return (nb_pipes);
}

t_fds *init_fds(t_token *token)
{
	t_fds *fds;
	int i;

	fds = ft_calloc(1, sizeof(t_fds));
	if (!fds)
		return (NULL);
	fds->nb_pipes = get_number_of_pipes(token);
	fds->pipes = ft_calloc(fds->nb_pipes, sizeof(int *));
	if (!fds->pipes)
		return (NULL);
	i = 0;
	while (i < fds->nb_pipes)
	{
		fds->pipes[i] = ft_calloc(2, sizeof(int));
		if (!fds->pipes[i])
			return (NULL);
		if (pipe(fds->pipes[i]) == -1)
		{
			perror("pipe");
			return (NULL);
		}
		i++;
	}
	return (fds);
}
