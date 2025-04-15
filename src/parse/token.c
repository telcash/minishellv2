/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:24:45 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/15 18:01:03 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_new_token_data(char *line, int start, int *i, t_shell *shell)
{
	(void)shell;
	char	*word;
	//char	*token_data;

	word = ft_substr(line, start, *i - start);
	//token_data = trim_quotes_and_expand(word, shell);
	//free(word);
	return (word);
}

static int	tokenize_word(char *line, int *i, t_shell *shell)
{
	char	quote;
	int		start;
	char	*token_data;

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
	if (quote == '\'')
		return (ft_error_concat(2, UN_TOKEN_ERR, "`''"), 1);
	if (quote == '"')
		return (ft_error_concat(2, UN_TOKEN_ERR, "`\"'"), 1);
	token_data = get_new_token_data(line, start, i, shell);
	append_token(token_data, WORD, shell);
	return (0);
}

static int	tokenize_separator(char *line, int *i, t_shell *shell)
{
	if (line[*i] == '|')
		append_token(ft_substr(line, *i, 1), PIPE, shell);
	else if (line[*i] == '<')
	{
		if (line[*i + 1] == '<')
			append_token(ft_substr(line, (*i)++, 2), HERE_DOC, shell);
		else
			append_token(ft_substr(line, *i, 1), IN, shell);
	}
	else if (line[*i] == '>')
	{
		if (line[*i + 1] == '>')
			append_token(ft_substr(line, (*i)++, 2), APPEND, shell);
		else
			append_token(ft_substr(line, *i, 1), OUT, shell);
	}
	else
		return (1);
	(*i)++;
	return (0);
}

static int	tokenize(char *line, t_shell *shell)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (!isseparator(line[i]))
		{
			if (tokenize_word(line, &i, shell))
				return (1);
		}
		else
		{
			if (tokenize_separator(line, &i, shell))
				return (1);
		}
	}
	return (0);
}

void	get_token(char *line, t_shell *shell)
{
	char *expanded;

	shell->token = (t_token **)malloc(sizeof(t_token *));
	if (!shell->token)
		shell->token = NULL;
	*(shell->token) = NULL;
	expanded = trim_quotes_and_expand(line, shell);
	if (tokenize(expanded, shell))
	{
		free_token(shell->token);
		shell->token = NULL;
		return ;
	}
	if (verify_token(shell->token))
	{
		free_token(shell->token);
		shell->token = NULL;
		return ;
	}
}
