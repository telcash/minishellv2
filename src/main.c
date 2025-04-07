/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 08:38:43 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/07 15:51:55 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	verify_input(int argc, char **argv)
{
	if (argc && argv)
		return ;
	else
		ft_exit_error(INV_ARG_ERR, EXIT_FAILURE, NULL);
}

static void	process_line(char *line, t_shell *shell)
{
	add_history(line);
	g_interactive = 0;
	get_token(line, shell);
	free(line);
	pipeline(shell);
	free_token(shell->token);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*line;

	verify_input(argc, argv);
	set_signal();
	init_minishell(&shell, envp);
	while (1)
	{
		g_interactive = INTERACTIVE;
		line = readline("minishell> ");
		if (!line)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			exit(0);
		}
 		else if (!*line)
			free(line);
		else
			process_line(line, shell);
	}
	return (free_shell(shell), 0);
}
