/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:02:34 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/29 09:44:00 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int process_in(char *file)
{
    int in;
    
    in = open(file, O_RDONLY, 0644);
    if (in == -1)
        perror(file);
    return (in);
}