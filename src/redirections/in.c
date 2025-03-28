/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:02:34 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/28 17:12:48 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int process_in(char *file)
{
    int in;
    
    in = open(file, O_RDONLY, 0644);
    if (in == -1)
    {
        perror(file);
        in = dup(STDIN_FILENO);
        return (in);
    }
    return (in);
}