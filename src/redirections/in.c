/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:02:34 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/11 12:13:05 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	process_in(char *file, char **err_msg)
{
	int		in;
	char	*tmp;

	in = -1;
	if (!*err_msg)
		in = open(file, O_RDONLY, 0644);
	if (in == -1)
	{
		tmp = ft_strjoin3("minishell: ", file, ": ");
		*err_msg = ft_strjoin(tmp, strerror(errno));
		free(tmp);
	}
	return (in);
}
