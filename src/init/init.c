/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:05:29 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/04 09:27:32 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_env(t_shell *shell, char **envp)
{
	int	i;

	if (!envp || !*envp)
		return ;
	shell->env = malloc(sizeof(t_env *));
	if (!shell->env)
		ft_error(MALLOC_ERR, 1, shell);
	i = 0;
	(*shell->env) = NULL;
	while (envp[i])
		upsert_env(shell, envp[i++]);
}

void	init_minishell(t_shell **shell, char **envp)
{
	*shell = malloc(sizeof(t_shell));
	if (!*shell)
		ft_error(MALLOC_ERR, 1, NULL);
	(*shell)->home = getenv("HOME");
	(*shell)->path = getcwd(NULL, 0);
	(*shell)->oldpath = NULL;
	(*shell)->pipes = NULL;
	(*shell)->com_count = 0;
	(*shell)->last_exit_status = 0;
	(*shell)->launched_procs = 0;
	(*shell)->token = NULL;
	init_env(*shell, envp);
}
