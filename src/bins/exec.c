/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:28:14 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/04 13:58:12 by carlossalaz      ###   ########.fr       */
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
static void copy_env_to_array(char **env_array, t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		if (env->name)
		{
			if (env->value)
				env_array[i] = ft_strjoin3(env->name, "=", env->value);
			else
				env_array[i] = ft_strdup(env->name);
			i++;
		}
		env = env->next;
	}
	env_array[i] = NULL;
}

static char **env_to_array(t_env *env)
{
	int len;
	t_env *tmp;
	char **env_array;

	if (!env)
		return (NULL);
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
	copy_env_to_array(env_array, env);
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

void exec_bin(t_shell *shell, char **cmdargs)
{
	char *path;
	char **envp;

	envp = env_to_array(*shell->env);
	if (ft_strchr(cmdargs[0], '/'))
		path = ft_strdup(cmdargs[0]);
	else
		path = get_path(cmdargs[0], shell->env);
	if (path == NULL)
	{
		ft_error_concat(3, "minishell: ", cmdargs[0], ": command not found");
		free_split(envp);
		free_shell(shell);
		free(cmdargs);
		exit(127);
	}
	if (execve(path, cmdargs, envp) == -1)
	{
		ft_error_concat(3, "minishell: ", cmdargs[0], strerror(errno));
		free(path);
		free_split(envp);
		free_shell(shell);
		free(cmdargs);
		exit(1);
	}
}
