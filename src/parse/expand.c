/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:42:10 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/03 10:21:51 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*append_to_expanded_data(char *expanded_data, char *data_segment)
{
	char	*new_expanded_data;

	if (!data_segment)
		return (expanded_data);
	if (!expanded_data)
		return (ft_strdup(data_segment));
	new_expanded_data = ft_strjoin(expanded_data, data_segment);
	free(expanded_data);
	return (new_expanded_data);
}

static char	*append_not_env_var(char *expanded_data, char *data, int *i)
{
	int		end;
	char	*tmp;
	char	*new_expanded_data;

	end = *i;
	while (data[end] && data[end] != '$')
		end++;
	tmp = ft_substr(data, *i, end - *i);
	new_expanded_data = append_to_expanded_data(expanded_data, tmp);
	free(tmp);
	*i = end;
	return (new_expanded_data);
}

static char	*append_last_exit_code(char *expanded_data, int *i, t_shell *shell)
{
	char	*last_status;

	last_status = ft_itoa(shell->last_exit_status);
	expanded_data = append_to_expanded_data(expanded_data, last_status);
	free(last_status);
	*i += 2;
	return (expanded_data);
}

static char	*append_env_var_value(char *expanded_data, char *data, int *i,
		t_shell *shell)
{
	int		end;
	char	*tmp;
	char	*new_expanded_data;

	end = *i + 1;
	while (data[end] && data[end] != '$')
		end++;
	tmp = ft_substr(data, *i + 1, end - *i - 1);
	new_expanded_data = append_to_expanded_data(expanded_data,
			get_env_var_value(shell, tmp));
	free(tmp);
	*i = end;
	return (new_expanded_data);
}

char	*expand_variable(char *data, t_shell *shell)
{
	char	*expanded_data;
	int		i;

	expanded_data = NULL;
	i = 0;
	while (data[i])
	{
		if (data[i] != '$')
			expanded_data = append_not_env_var(expanded_data, data, &i);
		else if (data[i + 1] == '?')
			expanded_data = append_last_exit_code(expanded_data, &i, shell);
		else
			expanded_data = append_env_var_value(expanded_data, data, &i,
					shell);
	}
	return (expanded_data);
}
