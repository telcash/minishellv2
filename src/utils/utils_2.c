/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 22:44:57 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/12 14:55:42 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	sort_env(char **env)
{
	int		count;
	int		i;
	int		j;
	char	*temp;

	count = 0;
	i = 0;
	while (env[count] != NULL)
		count++;
	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_sorted_env(t_env **env, int out)
{
	char	**env_arr;
	int		i;

	if (!env || !*env)
		return ;
	env_arr = env_to_array(*env);
	sort_env(env_arr);
	i = 0;
	while (env_arr[i])
	{
		ft_putstr_fd("declare -x ", out);
		ft_putendl_fd(env_arr[i], out);
		i++;
	}
	free_split(env_arr);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	isseparator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
