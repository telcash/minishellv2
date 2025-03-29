/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:45:23 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/29 13:45:52 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(t_shell *minishell, char **cmdargs)
{
	t_env	*prev;
	t_env	*curr;
	int			i;

	prev = NULL;
	i = 1;
	while (cmdargs[i])
	{
		curr = *(minishell->env);
		while (curr)
		{
			if (strcmp(curr->name, cmdargs[i]) == 0)
			{
				if (prev)
					prev->next = curr->next;
				free(curr->name);
				free(curr->value);
				free(curr);
                break ;
			}
			else
			{
				prev = curr;
				curr = curr->next;
			}
		}
		i++;
	}
	return (0);
}
