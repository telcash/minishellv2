/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:24:45 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/03 11:23:07 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	tokenize_word(char *line, int *i, t_token **token, t_shell *shell)
{
	char	quote;
	int		start;
	char	*word;

	start = *i;
	quote = '\0';
	while (line[*i] && (quote || (!quote && !isseparator(line[*i])
				&& !ft_isspace(line[*i]))))
	{
		if ((line[*i] == '\'' || line[*i] == '"') && !quote)
			quote = line[*i];
		else if (line[*i] == quote)
			quote = '\0';
		(*i)++;
	}
	if (quote)
		return (1);
	word = ft_substr(line, start, *i - start);
	append_token(token, trim_quotes(word), WORD, shell);
	free(word);
	return (0);
}

static int	tokenize_separator(char *line, int *i, t_token **token, t_shell *shell)
{
	if (line[*i] == '|')
		append_token(token, ft_substr(line, *i, 1), PIPE, shell);
	else if (line[*i] == '<')
	{
		if (line[*i + 1] == '<')
			append_token(token, ft_substr(line, (*i)++, 2), HERE_DOC, shell);
		else
			append_token(token, ft_substr(line, *i, 1), IN, shell);
	}
	else if (line[*i] == '>')
	{
		if (line[*i + 1] == '>')
			append_token(token, ft_substr(line, (*i)++, 2), APPEND, shell);
		else
			append_token(token, ft_substr(line, *i, 1), OUT, shell);
	}
	else
		return (1);
	(*i)++;
	return (0);
}

static int	tokenize(char *line, t_token **token, t_shell *shell)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (!isseparator(line[i]))
		{
			if (tokenize_word(line, &i, token, shell))
				return (1);
		}
		else
		{
			if (tokenize_separator(line, &i, token, shell))
				return (1);
		}
	}
	return (0);
}

t_token	**get_token(char *line, t_shell *shell)
{
	t_token	**token;

	token = (t_token **)malloc(sizeof(t_token *));
	if (!token)
		return (NULL);
	*token = NULL;
	if (tokenize(line, token, shell))
		return (NULL);
 	if (verify_token(token))
		return (NULL);
	return (token);
}