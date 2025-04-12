/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:19:39 by csalazar          #+#    #+#             */
/*   Updated: 2025/04/12 14:43:40 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*append_word_segment(char *data, char *word, int start, int end)
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

static char	*get_expanded_variable(int start, int end, char *word,
		t_shell *shell)
{
	char	*tmp1;
	char	*tmp2;

	if (end - start > 1)
	{
		tmp1 = ft_substr(word, start + 1, end - start - 1);
		tmp2 = get_env_value(shell->env, tmp1);
		free(tmp1);
		if (tmp2)
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

static void	toggle_quote(char quote, char *s_quote, char *d_quote)
{
	if (quote == '\'')
	{
		if (*s_quote)
			*s_quote = '\0';
		else
			*s_quote = quote;
	}
	else if (quote == '"')
	{
		if (*d_quote)
			*d_quote = '\0';
		else
			*d_quote = quote;
	}
}

char	*trim_quotes_and_expand(char *word, t_shell *shell)
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
	while (word[i])
	{
		start = i;
		while (word[i] && ((word[i] != '\'' && word[i] != '"' && word[i] != '$')
					|| (word[i] == '$' && s_quote) || (word[i] == '\''
					&& d_quote) || (word[i] == '"' && s_quote)))
			i++;
		data = append_word_segment(data, word, start, i);
		if (word[i] == '$' && !s_quote)
			data = add_expanded_variable(data, word, &i, shell);
		else if ((word[i] == '\'' && !d_quote) || (word[i] == '"' && !s_quote))
			toggle_quote(word[i++], &s_quote, &d_quote);				
	}
	return (data);
}
