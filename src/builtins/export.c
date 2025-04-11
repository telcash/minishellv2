/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:44:17 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/11 11:04:29 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_export(t_shell *minishell, char **cmdargs, int out)
{
	int	i;
	int	upserted;

	i = 1;
	if (!cmdargs[i])
	{
		print_sorted_env(minishell, out);
		return (0);
	}
	while (cmdargs[i])
	{
		upserted = upsert_env(minishell, cmdargs[i]);
		if (upserted == -1)
			ft_error_concat(3, "export: `", cmdargs[i],
				"': not a valid identifier");
		i++;
	}
	return (0);
}
