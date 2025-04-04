/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:12:00 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/04 14:10:43 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_shell *minishell, int out)
{
	if (minishell->path)
	{
		ft_putendl_fd(minishell->path, out);
		return (0);
	}
	else
		ft_error(NO_PATH_ERR);
	return (0);
}