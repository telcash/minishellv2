/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:16:33 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/26 14:50:48 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:46:02 by csalazar          #+#    #+#             */
/*   Updated: 2025/03/18 17:19:04 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void print_exit_error(char *cmd)
{
	char *temp;

	temp = ft_strjoin("minishell: exit: ", cmd);
	ft_putstr_fd(temp, 2);
	free (temp);
	ft_putendl_fd(": numeric argument required", 2);
}

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int ft_exit_pipes(char **cmdargs)
{
	if (cmdargs[1] && !is_numeric(cmdargs[1]))
	{
		print_exit_error(cmdargs[1]);
		return (2);
	}
	if (cmdargs[1] && cmdargs[2])
		ft_putendl_fd("minishell: exit: too many arguments",
				STDERR_FILENO);
	return (0);
}

static void ft_exit_no_pipes(t_shell *minishell, char **cmdargs)
{
	int exit_num;
	
	if (cmdargs[1] && !is_numeric(cmdargs[1]))
	{
		ft_putendl_fd("exit", 2);
		print_exit_error(cmdargs[1]);
		exit(2);
	}
	if (cmdargs[1] && cmdargs[2])
	{
		ft_putendl_fd("exit\nminishell: exit: too many arguments",
				STDERR_FILENO);
		return ;
	}
	if (cmdargs[1])
	{
		exit_num = atoi(cmdargs[1]) % 256;
		printf("exit\n");
		exit(exit_num);
	}
	printf("exit\n");
	free_shell(minishell);
	exit(0);
}

int	ft_exit(t_shell *minishell, char **cmdargs)
{
	if (minishell->fds->nb_pipes > 0)
		return (ft_exit_pipes(cmdargs));
	else
		ft_exit_no_pipes(minishell, cmdargs);
	return (0);
}
