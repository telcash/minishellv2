/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 09:53:39 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/30 09:57:21 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void handle_signal(int sig)
{
    if (sig == SIGINT)
    {
        (void)sig;
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    if (sig == SIGQUIT)
        (void)sig;
}

void set_signal(void)
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
    if (sigaction(SIGQUIT, &sa_int, NULL) == -1)
    {
        perror("ERROR registering SIGQUIT handler");
        exit(EXIT_FAILURE);
    }
}