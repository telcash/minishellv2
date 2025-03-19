/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:09:52 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/19 09:29:18 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_error(char *message, int status, t_shell *shell)
{
    if (shell)
        free_shell(shell);
    if (message)
        ft_putendl_fd(message, 2);
    exit(status);
}