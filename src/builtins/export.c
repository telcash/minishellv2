/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:44:17 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/04 10:35:17 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_export(t_shell *minishell, char **cmdargs)
{
	int			i;
	int			upserted;

	i = 1;
	if (!cmdargs[i])
	{
		ft_env(minishell, 1);
		return (0);
	}
	while (cmdargs[i])
	{
		upserted = upsert_env(minishell, cmdargs[i]);
		if (upserted == -1)
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(cmdargs[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		i++;
	}
	return (0);
}
