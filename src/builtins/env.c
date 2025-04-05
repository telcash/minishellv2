/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:43:50 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/29 13:44:06 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_shell *minishell, int out)
{
	t_env	*tmp;

	tmp = *(minishell->env);
	while (tmp)
	{
		ft_putstr_fd(tmp->name, out);
		ft_putstr_fd("=", out);
		ft_putendl_fd(tmp->value, out);
		tmp = tmp->next;
	}
	return (0);
}
