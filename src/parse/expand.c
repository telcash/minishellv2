/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:36:10 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/21 11:37:58 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_expanded_variable(int start, int end, char *word,
		t_shell *shell)
{
	char	*tmp1;
	char	*tmp2;

	if (end - start > 1)
	{
		tmp1 = ft_substr(word, start + 1, end - start - 1);
		tmp2 = get_env_value(shell->env, tmp1);
		if (ft_strcmp(tmp1, "PWD") == 0 && !tmp2)
			tmp2 = shell->pwd;
		free(tmp1);
		if (tmp2 && ft_strchr(tmp2, '\''))
			return (ft_strjoin3("\"", tmp2, "\""));
		else if (tmp2)
			return (ft_strdup(tmp2));
		else
			return (NULL);
	}
	else
		return (NULL);
}
static char	*add_expanded_variable(char *data, char *word, int *i,
		t_shell *shell)
{
	char	*exp_var;
	int		start;
	int		end;

	start = *i;
	if (word[start + 1] == '?')
	{
		exp_var = ft_itoa(shell->last_exit_status);
		*i += 2;
		end = start + 2;
	}
	else if (word[start + 1] == '_')
	{
		exp_var = ft_strdup(shell->_);
		*i += 2;
		end = start + 2;
	}
	else
	{
		end = start + 1;
		while (word[end] && (ft_isalnum(word[end]) || word[end] == '_'))
			end++;
		exp_var = get_expanded_variable(start, end, word, shell);
	}
	*i = end;
	if (exp_var)
	{
		data = append_word_segment(data, exp_var, 0, ft_strlen(exp_var));
		free(exp_var);
	}
	return (data);
}

char	*expand_here_doc(char *line, int has_quotes, t_shell *shell)
{
	char	*data;
	int		i;
	int		start;

	if (has_quotes)
		return (ft_strdup(line));
	data = NULL;
	i = 0;
	while (line[i])
	{
		start = i;
		while (line[i] && line[i] != '$')
			i++;
		data = append_word_segment(data, line, start, i);
		if (line[i] == '$')
			data = add_expanded_variable(data, line, &i, shell);
	}
	return (data);
}
char	*append_word_segment(char *data, char *word, int start, int end)
{
	char	*tmp;
	char	*new_data;

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

char	*expand_line(char *line, t_shell *shell)
{
	char	*data;
	char	s_quote;
	char	d_quote;
	int		start;
	int		i;

	data = NULL;
	s_quote = '\0';
	d_quote = '\0';
	i = 0;
	while (line[i])
	{
		start = i;
		while (line[i] && ((line[i] != '$') || (line[i] == '$'
					&& s_quote)))
		{
			if ((line[i] == '\'' && !d_quote) || (line[i] == '"' && !s_quote))
				toggle_quote(line[i], &s_quote, &d_quote);
			i++;
		}
		data = append_word_segment(data, line, start, i);
		if (line[i] == '$' && !s_quote)
			data = add_expanded_variable(data, line, &i, shell);
	}
	return (data);
}
