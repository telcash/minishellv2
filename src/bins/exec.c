/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:28:14 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/29 13:37:22 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *ft_strjoin3(char *s1, char *s2, char *s3)
{
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    size_t len3 = ft_strlen(s3);
    char *result = malloc(len1 + len2 + len3 + 1);
    if (!result)
        return (NULL);
    ft_strlcpy(result, s1, len1 + 1);
    ft_strlcat(result, s2, len1 + len2 + 1);
    ft_strlcat(result, s3, len1 + len2 + len3 + 1);
    return (result);
}

static char **env_to_array(t_env *env)
{
	int len;
	int i;
	t_env *tmp;
	char **env_array;
	char *entry;

	tmp = env;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	env_array = ft_calloc(len + 1, sizeof(char *));
	if (!env_array)
		return (NULL);
	tmp = env;
	i = 0;
	while (i < len)
	{
		if (!tmp->name)
		{
			env_array[i] = NULL;
			continue;
		}
		if (tmp->value)
			entry = ft_strjoin3(tmp->name, "=", tmp->value);
		else
			entry = ft_strdup(tmp->name);
		env_array[i] = entry;
		tmp = tmp->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

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
	char **envp;

	envp = env_to_array(*minishell->env);
	if (ft_strchr(cmdargs[0], '/'))
		path = ft_strdup(cmdargs[0]);
	else
		path = get_path(cmdargs[0], minishell->env);
	if (path == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmdargs[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}

	if (execve(path, cmdargs, envp) == -1)
	{
		free(path);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmdargs[0], 2);
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
}
