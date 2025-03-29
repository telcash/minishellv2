/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:41:58 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/29 13:42:40 by carlossalaz      ###   ########.fr       */
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

static void	update_path(t_shell *minishell)
{
	if (minishell->oldpath)
		free(minishell->oldpath);
	minishell->oldpath = ft_strdup(minishell->path);
	free(minishell->path);
	minishell->path = getcwd(NULL, 0);
	if (!minishell->path)
		perror("Error updating the path");
}

void	ft_cd_no_pipes(t_shell *minishell, char **cmdargs)
{
	if (cmdargs[2])
	{
		perror("too many arguments");
		return ;
	}
	if (!cmdargs[1])
	{
		if (!minishell->home || chdir(minishell->home) != 0)
			perror("Error accessing HOME");
		else
			update_path(minishell);
	}
	else if (ft_strcmp(cmdargs[1], "..") == 0)
	{
		if (chdir("..") != 0)
			perror("Error accessing directory");
		else
			update_path(minishell);
	}
	else if (ft_strcmp(cmdargs[1], "-") == 0)
	{
		if (chdir(minishell->oldpath) != 0)
			perror("Error accessing directory");
		else
			update_path(minishell);
	}
	else
	{
		if (chdir(cmdargs[1]) != 0)
			perror("Error accesing");
		else
			update_path(minishell);
	}
}

int ft_cd(t_shell *minishell, char **cmdargs)
{
	if (minishell->pipes->nb_pipes > 0)
		return (0);
	else
		ft_cd_no_pipes(minishell, cmdargs);
	return (0);
}
