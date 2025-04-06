/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:19:39 by csalazar          #+#    #+#             */
/*   Updated: 2025/04/06 23:05:38 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *append_word_segment(char *data, char *word, int start, int end)
{
	char *tmp;
	char *new_data;

	tmp = ft_substr(word, start, end - start);
	if (!tmp)
		return (data);
	if (!data)
		data = ft_strdup("");
	new_data = ft_strjoin(data, tmp);
	free(tmp);
	if (!new_data)
		return (data);
	free(data);
	return (new_data);
}
static char *get_expanded_variable(int start, int end, char *word, t_shell *shell)
{
	char *tmp1;
	char *tmp2;

	if (end - start > 1)
	{
		tmp1 = ft_substr(word, start + 1, end - start - 1);
		tmp2 = get_env_value(shell, tmp1);
		free(tmp1);
		if (tmp2)
			return (ft_strdup(tmp2));
		else
			return (NULL);
	}
	else
		return (NULL);
}

static char	*add_expanded_variable(char *data, char *word, int *i, t_shell *shell)
{
	char	*expanded_var;
	int		start;
	int		end;

	start = *i;
	if (word[start + 1] == '?')
	{
		expanded_var = ft_itoa(shell->last_exit_status);
		*i += 2;
		end = start + 2;
	}
	else
	{
		end = start + 1;
		while (word[end] && (ft_isalnum(word[end]) || word[end] == '_'))
			end++;
		expanded_var = get_expanded_variable(start, end, word, shell);
	}
	*i = end;
	if (expanded_var)
	{
		data = append_word_segment(data, expanded_var, 0, ft_strlen(expanded_var));
		free(expanded_var);
	}
	return (data);
}

char *trim_quotes_and_expand(char *word, t_shell *shell)
{
	char *data;
	char quote;
	int start;
	int i;

	data = NULL;
	quote = '\0';
	i = 0;
	while (word[i])
	{
		start = i;
		while (word[i] && ((!quote && word[i] != '\'' && word[i] != '"') || (quote && word[i] != quote)) && word[i] != '$')
			i++;
		data = append_word_segment(data, word, start, i);
		if (word[i] == '$')
			data = add_expanded_variable(data, word, &i, shell);
		else if ((word[i] == '\'' || word[i] == '"') && !quote)
			quote = word[i++];
		else if (word[i] == quote)
			quote = '\0';
		else
			i++;
	}
	return (data);
}
