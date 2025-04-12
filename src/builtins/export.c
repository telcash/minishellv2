/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:44:17 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/12 12:37:05 by carlossalaz      ###   ########.fr       */
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
		//luego de imprimir el env imprimiría sólo lo de export
		return (0);
	}
	while (cmdargs[i])
	{
		// Si el argumento es válido lo guardo en la estructura del export
		// Esta estructura del export hay que inicializarla al inicio del minishell
		// o en vez de una estructura podría mejor ser un **str
		upserted = upsert_env(minishell, cmdargs[i]);
		if (upserted == -1)
			ft_error_concat(3, "export: `", cmdargs[i],
				"': not a valid identifier");
		i++;
	}
	return (0);
}
