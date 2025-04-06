/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:41:58 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/04 14:47:38 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	update_path(t_shell *shell)
{
	if (shell->oldpath)
		free(shell->oldpath);
	shell->oldpath = ft_strdup(shell->path);
	if (find_env_var_by_name(shell, "OLDPWD"))
	append_or_update(shell, ft_strdup("OLDPWD"), ft_strdup(shell->path));
	free(shell->path);
	shell->path = getcwd(NULL, 0);
	if (find_env_var_by_name(shell, "PWD"))
	append_or_update(shell, ft_strdup("PWD"), ft_strdup(shell->path));
	return (0);
	//	append_or_update(shell, "OLDPWD", get_env_value(shell, "PWD"));
	// free(shell->path);
	// shell->path = getcwd(NULL, 0);
	// if (!shell->path)
	// 	return (ft_error(PATH_UPDATE_ERR), 1);
	// return (0);
}

static int	ft_cd_no_pipes2(t_shell *shell, char **cmdargs)
{
	if (ft_strcmp(cmdargs[1], "-") == 0)
	{
		if (find_env_var_by_name(shell, "OLDPWD"))
		{
			if (chdir(shell->oldpath) != 0)
				return (ft_error(DIR_ACCESS_ERR), 1);
			else
				return (update_path(shell));
		}
		else
			return(ft_error("minishell: cd: OLDPWD no está establecido"), 1);

	}
	else
	{
		if (chdir(cmdargs[1]) != 0)
			return (ft_error(NO_FILE_ERR),1);
		else
			return (update_path(shell));
	}
}

static int	ft_cd_no_pipes(t_shell *shell, char **cmdargs)
{
	char	*home;

	if (len_2d_array(cmdargs) > 2)
		return (ft_error(CD_TOO_MANY_ARGS_ERR), 1);
	if (!cmdargs[1])
	{
		home = get_env_value(shell, "HOME");
		if (!home || chdir(home) != 0)
			return (ft_error(CD_NO_HOME_ERR), 1);
		else
			return (update_path(shell));
	}
	else if (ft_strcmp(cmdargs[1], "..") == 0)
	{
		if (chdir("..") != 0)
			return (ft_error(DIR_ACCESS_ERR), 1);
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
