/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:24:45 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/19 11:25:00 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	tokenize_word(char *line, int *i, t_token **token)
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
	append_token(token, trim_quotes(word), WORD);
	free(word);
	return (0);
}

static int	tokenize_separator(char *line, int *i, t_token **token)
{
	if (line[*i] == '|')
		append_token(token, ft_substr(line, *i, 1), PIPE);
	else if (line[*i] == '<')
	{
		if (line[*i + 1] == '<')
			append_token(token, ft_substr(line, (*i)++, 2), HERE_DOC);
		else
			append_token(token, ft_substr(line, *i, 1), IN);
	}
	else if (line[*i] == '>')
	{
		if (line[*i + 1] == '>')
			append_token(token, ft_substr(line, (*i)++, 2), APPEND);
		else
			append_token(token, ft_substr(line, *i, 1), OUT);
	}
	else
		return (1);
	(*i)++;
	return (0);
}

static int	tokenize(char *line, t_token **token)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (!isseparator(line[i]))
		{
			if (tokenize_word(line, &i, token))
				return (1);
		}
		else
		{
			if (tokenize_separator(line, &i, token))
				return (1);
		}
	}
	return (0);
}
static int verify_token(t_token **token)
{
	t_token *tmp;

	tmp = *token;
	if (!tmp || (tmp && tmp->type == PIPE))
		return (1);
	while (tmp)
	{
		if (tmp->type == IN || tmp->type == OUT || tmp->type == HERE_DOC
			|| tmp->type == APPEND || tmp->type == PIPE)
		{
			if (!tmp->next || tmp->next->type == IN || tmp->next->type == OUT 
				|| tmp->next->type == APPEND || tmp->next->type == HERE_DOC || tmp->next->type == PIPE)
				return (1);
			else if(tmp->next && tmp->type != PIPE)
			{
				tmp->data = tmp->next->data;
				tmp->next = tmp->next->next;
			}
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}

t_token	**get_token(char *line)
{
	t_token	**token;

	token = (t_token **)malloc(sizeof(t_token *));
	if (!token)
		return (NULL);
	*token = NULL;
	if (tokenize(line, token))
		return (NULL);
 	if (verify_token(token))
		return (NULL);
	return (token);
}