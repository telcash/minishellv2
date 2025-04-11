/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:41:58 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/11 11:03:46 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	update_path(t_shell *shell)
{
	if (shell->oldpwd)
		free(shell->oldpwd);
	shell->oldpwd = ft_strdup(shell->pwd);
	if (find_env_var_by_name(shell, "OLDPWD"))
	{
		if (!find_env_var_by_name(shell, "PWD") && get_env_value(shell,
				"OLDPWD")[0])
			append_or_update(shell, ft_strdup("OLDPWD"), ft_strdup(""));
		else
			append_or_update(shell, ft_strdup("OLDPWD"), ft_strdup(shell->pwd));
	}
	free(shell->pwd);
	shell->pwd = getcwd(NULL, 0);
	if (find_env_var_by_name(shell, "PWD"))
		append_or_update(shell, ft_strdup("PWD"), ft_strdup(shell->pwd));
	return (0);
}

static int	ft_cd_no_pipes2(t_shell *shell, char **cmdargs)
{
	if (ft_strcmp(cmdargs[1], "-") == 0)
	{
		if (find_env_var_by_name(shell, "OLDPWD"))
			ft_putendl_fd(get_env_value(shell, "OLDPWD"), STDOUT_FILENO);
		else if (shell->oldpwd[0])
			ft_putendl_fd(shell->oldpwd, STDOUT_FILENO);
		if (find_env_var_by_name(shell, "OLDPWD"))
		{
			if (!get_env_value(shell, "OLDPWD")[0])
				return (update_path(shell));
			if (chdir(get_env_value(shell, "OLDPWD")) != 0)
				return (ft_error(DIR_ACCESS_ERR), 1);
			else
				return (update_path(shell));
		}
		else if (shell->oldpwd[0])
			if (chdir(shell->oldpwd) != 0)
				return (ft_error(DIR_ACCESS_ERR), 1);
			else
				return (update_path(shell));
		else
			return (ft_error("minishell: cd: OLDPWD not set"), 1);
	}
	else
	{
		if (chdir(cmdargs[1]) != 0)
			return (ft_error(NO_FILE_ERR), 1);
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
		if (!home)
			return (ft_error(CD_NO_HOME_ERR), 1);
		else
		{
			if (chdir(home) != 0)
			{
				if (!home[0])
					return (0);
				return (ft_error_concat(2, "minishell: cd: ", NO_FILE_ERR), 1);
			}
			return (update_path(shell));
		}
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
