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

int	ft_pwd(t_shell *shell, int out)
{
	// if (!get_env_value(shell, "PWD"))
	// 	append_or_update(shell, "PWD", getcwd(NULL, 0));
	// ft_putendl_fd(pwd, out);
	// free(pwd);
// 		return (0);
// 	if (shell->path)
// 	{
	ft_putendl_fd(shell->path, out);
// 	}
// 	else
// 		ft_error(NO_PATH_ERR);
	return (0);
}