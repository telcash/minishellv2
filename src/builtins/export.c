/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:44:17 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/29 18:30:57 by carlossalaz      ###   ########.fr       */
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
			printf("export: `%s': not a valid identifier\n", cmdargs[i]);
		i++;
	}
	return (0);
}
