/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:09:52 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/04 09:21:29 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit_error(char *message, int status, t_shell *shell)
{
	if (shell)
		free_shell(shell);
	if (message)
		ft_putendl_fd(message, 2);
	exit(status);
}
