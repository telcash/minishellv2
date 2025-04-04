/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 08:38:43 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/04 09:27:35 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	verify_input(int argc, char **argv)
{
	if (argc && argv)
		return ;
	else
		ft_exit_error(INV_ARG_ERR, 1, NULL);
}

static void	process_line(char *line, t_shell *shell)
{
	add_history(line);
	g_interactive = 0;
	shell->token = get_token(line, shell);
	free(line);
	pipeline(shell);
	free_token(shell->token);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*line;

	verify_input(argc, argv);
	init_minishell(&shell, envp);
	set_signal();
	while (1)
	{
		g_interactive = 1;
		line = readline("minishell> ");
		if (!line)
		{
			ft_putendl_fd("exit", 2);
			exit(0);
		}
		if (line && *line)
			process_line(line, shell);
	}
	return (free_shell(shell), 0);
}
