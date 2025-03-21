/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 08:38:43 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/19 11:01:30 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void verify_input(int argc, char **argv)
{
    if (argc && argv)
        return ;
    else
        ft_putstr_fd("Error: invalid input\n", 2);
    exit(1);
}

int main(int argc, char **argv, char **envp)
{
    t_shell *shell;

    verify_input(argc, argv);
    init_minishell(&shell, envp);
    return (0);
}