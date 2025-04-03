/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:43:02 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/03 08:44:37 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_echo(char **cmdargs, int out)
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
		ft_putstr_fd(cmdargs[i], out);
		if (cmdargs[i + 1])
			write(out, " ", 1);
		i++;
	}
	if (n == 0)
		write(out, "\n", 1);
    return (0);
}
