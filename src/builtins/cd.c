/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:41:58 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/04 09:52:23 by csalazar         ###   ########.fr       */
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

static int	len_2d_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (*arr)
	{
		arr++;
		i++;
	}
	return (i);
}

static int	update_path(t_shell *minishell)
{
	if (minishell->oldpath)
		free(minishell->oldpath);
	minishell->oldpath = ft_strdup(minishell->path);
	free(minishell->path);
	minishell->path = getcwd(NULL, 0);
	if (!minishell->path)
		return (ft_putendl_fd("Error updating the path", 2), 1);
	return (0);
}
static int	ft_cd_no_pipes2(t_shell *shell, char **cmdargs)
{
	if (ft_strcmp(cmdargs[1], "-") == 0)
	{
		if (chdir(shell->oldpath) != 0)
			return (ft_putendl_fd("Error accessing directory", 2), 1);
		else
			return (update_path(shell));
	}
	else
	{
		if (chdir(cmdargs[1]) != 0)
			return (ft_putendl_fd("minishell: cd: No such file or directory",
									2),
					1);
		else
			return (update_path(shell));
	}
}

static int	ft_cd_no_pipes(t_shell *shell, char **cmdargs)
{
	char	*home;

	if (len_2d_array(cmdargs) > 2)
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	if (!cmdargs[1])
	{
		home = get_env_value(shell, "HOME");
		if (!home || chdir(home) != 0)
			return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
		else
			return (update_path(shell));
	}
	else if (ft_strcmp(cmdargs[1], "..") == 0)
	{
		if (chdir("..") != 0)
			return (ft_putendl_fd("Error accessing directory", 2), 1);
		else
			return (update_path(shell));
	}
	else
		return (ft_cd_no_pipes2(shell, cmdargs));
}

int	ft_cd(t_shell *shell, char **cmdargs)
{
	if (shell->pipes->nb_pipes > 0)
		return (0);
	else
		return (ft_cd_no_pipes(shell, cmdargs));
}
