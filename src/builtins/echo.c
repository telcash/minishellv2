/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:43:02 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/29 13:43:21 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_echo(char **cmdargs)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (cmdargs[i] && ft_strcmp(cmdargs[i], "-n") == 0)
	{
		i++;
		n = 1;
	}
	while (cmdargs[i])
	{
		ft_putstr_fd(cmdargs[i], 1);
		if (cmdargs[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (n == 0)
		write(1, "\n", 1);
    return (0);
}
