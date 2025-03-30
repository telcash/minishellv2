/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 08:38:43 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/30 09:57:21 by carlossalaz      ###   ########.fr       */
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
    t_token **token;
    char *line;

    verify_input(argc, argv);
    init_minishell(&shell, envp);
    set_signal();
    while (1)
    {
        line = readline("minishell> ");
        if (!line)
            break ;
        if (line && *line)
        {
            add_history(line);
            token = get_token(line, shell);
            pipeline(token, shell);
            free(line);
            free_token(token);
        }
    }
    free_shell(shell);
    return (0);
}
