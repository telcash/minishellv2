/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:19:57 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/12 13:29:39 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	process_append(char *file, char **err_msg)
{
	int	out;
	char *tmp;

	out = -1;
	if (!*err_msg)
		out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out == -1 && !*err_msg)
	{
		tmp = ft_strjoin3("minishell: ", file, ": ");
		*err_msg = ft_strjoin(tmp, strerror(errno));
		free(tmp);
	}
	return (out);
}
