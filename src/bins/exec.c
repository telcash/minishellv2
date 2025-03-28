/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:28:14 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/26 22:42:19 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char **get_paths(t_env **env)
{
	char **paths;
	t_env *tmp;

	tmp = *env;
	while (tmp && ft_strncmp(tmp->name, "PATH", 4))
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp->value, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

static char *get_path(char *cmd, t_env **env)
{
	int i;
	char **paths;
	char *partial_path;
	char *path_cmd;

	paths = get_paths(env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
        partial_path = ft_strjoin(paths[i], "/");
        path_cmd = ft_strjoin(partial_path, cmd);
        free(partial_path);
        if (access(path_cmd, F_OK) == 0)
        {
            free_split(paths);
            return (path_cmd);
        }
        free(path_cmd);
        i++;
    }
	free_split(paths);
    return (NULL);
}

void exec_bin(t_shell *minishell, char **cmdargs)
{
	char *path;

	path = get_path(cmdargs[0], minishell->env);
	if (path == NULL)
	{
		printf("minishell: %s: command not found\n", cmdargs[0]);
		return ;
	}

	if (execve(path, cmdargs, NULL) == -1)
	{
		free(path);
		printf("minishell: %s: %s\n", cmdargs[0], strerror(errno));
		return ;
	}
}