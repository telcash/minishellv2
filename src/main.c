/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 08:38:43 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/03 12:01:14 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	verify_input(int argc, char **argv)
{
	if (argc && argv)
		return ;
	else
		ft_putstr_fd("Error: invalid input\n", 2);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	t_token	**token;
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
		{
			add_history(line);
			g_interactive = 0;
			token = get_token(line, shell);
			pipeline(token, shell);
			free(line);
			free_token(token);
		}
	}
	return (free_shell(shell), 0);
}
