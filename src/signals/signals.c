/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 09:53:39 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/01 19:32:22 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int g_interactive = 1;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		if (g_interactive)
		{
			write(STDOUT_FILENO, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 1);
			rl_redisplay();
		}
		else
			write(STDOUT_FILENO, "\n", 1);
	}
}

void	set_signal(void)
{
	struct sigaction sa_int;

	sa_int.sa_handler = handle_signal;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("ERROR registering SIGINT handler");
		exit(EXIT_FAILURE);
	}
	sa_int.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa_int, NULL) == -1)
	{
		perror("ERROR registering SIGQUIT handler");
		exit(EXIT_FAILURE);
	}
}