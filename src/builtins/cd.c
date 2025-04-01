/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:41:58 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/01 15:46:43 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:42:03 by csalazar          #+#    #+#             */
/*   Updated: 2025/03/18 17:18:33 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	update_path(t_shell *minishell)
{
	if (minishell->oldpath)
		free(minishell->oldpath);
	minishell->oldpath = ft_strdup(minishell->path);
	free(minishell->path);
	minishell->path = getcwd(NULL, 0);
	if (!minishell->path)
		return (perror("Error updating the path"), 1);
	return (0);
}

/* static int	ft_cd_no_pipes(t_shell *minishell, char **cmdargs)
{
	if (cmdargs[2])
		return (perror("too many arguments"), 1);
	if (!cmdargs[1])
	{
		if (!minishell->home || chdir(minishell->home) != 0)
			return (perror("Error accessing HOME"), 1);
		else
			return (update_path(minishell));
	}
	else if (ft_strcmp(cmdargs[1], "..") == 0)
	{
		if (chdir("..") != 0)
			return (perror("Error accessing directory"), 1);
		else
			return (update_path(minishell));
	}
	else if (ft_strcmp(cmdargs[1], "-") == 0)
	{
		if (chdir(minishell->oldpath) != 0)
			return (perror("Error accessing directory"), 1);
		else
			return (update_path(minishell));
	}
	else
	{
		if (chdir(cmdargs[1]) != 0)
			return (perror("Error accesing"), 1);
		else
			return (update_path(minishell));
	}
} */

static int ft_cd_no_pipes(t_shell *shell, char **cmdargs)
{
	if (cmdargs[2])
		return (perror("too many arguments"), 1);
	if (!cmdargs[1] && (!shell->home || chdir(shell->home) != 0))
		return (perror("Error accessing HOME"), 1);
	else if (ft_strcmp(cmdargs[1], "..") == 0 && chdir("..") != 0)
		return (perror("Error accessing directory"), 1);
	else if (ft_strcmp(cmdargs[1], "-") == 0 && chdir(shell->oldpath) != 0)
		return (perror("Error accessing directory"), 1);
	else if (chdir(cmdargs[1]) != 0)
		return (perror("Error accessing"), 1);
	else
		return (update_path(shell));
}

int ft_cd(t_shell *minishell, char **cmdargs)
{
	if (minishell->pipes->nb_pipes > 0)
		return (0);
	else
		return (ft_cd_no_pipes(minishell, cmdargs));
}
