/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfernan3 <dfernan3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:43:50 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/08 16:35:36 by dfernan3         ###   ########.fr       */
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
