/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfernan3 <dfernan3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:22:53 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/08 15:55:41 by dfernan3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cmd_is_builtin(char *com)
{
	return (ft_strcmp("pwd", com) == 0 || ft_strcmp("cd", com) == 0
		|| ft_strcmp("echo", com) == 0 || ft_strcmp("exit", com) == 0
		|| ft_strcmp("env", com) == 0 || ft_strcmp("export", com) == 0
		|| ft_strcmp("unset", com) == 0);
}

int	exec_built_in(t_shell *minishell, char **cmdargs, int out)
{
	int code;

	if (ft_strcmp("pwd", cmdargs[0]) == 0)
		code = ft_pwd(out);
	else if (ft_strcmp("cd", cmdargs[0]) == 0)
		code = ft_cd(minishell, cmdargs);
	else if (ft_strcmp("echo", cmdargs[0]) == 0)
		code = ft_echo(cmdargs, out);
	else if (ft_strcmp("exit", cmdargs[0]) == 0)
		code = ft_exit(minishell, cmdargs);
	else if(ft_strcmp("env", cmdargs[0]) == 0)
		code = ft_env(minishell, out);
	else if(ft_strcmp("export", cmdargs[0]) == 0)
		code = ft_export(minishell, cmdargs, out);
	else if(ft_strcmp("unset", cmdargs[0]) == 0)
		code = ft_unset(minishell, cmdargs);
	if (minishell->pipes->nb_pipes > 0)
		exit (code);
	return (0);
}
