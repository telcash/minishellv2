/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:19:39 by csalazar          #+#    #+#             */
/*   Updated: 2025/04/04 12:00:36 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token *get_last_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
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

void	append_token(char *data, t_token_type type, t_shell *shell)
{
	t_token	*curr_token;
	t_token	*last_token;
	t_token	*new_token;

	curr_token = *(shell->token);
	last_token = get_last_token(curr_token);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->data = expand_variable(data, shell);
	free(data);
	if (!new_token->data)
	{
		free(new_token);
		return ;
	}
	new_token->type = type;
	new_token->next = NULL;
	if (!last_token)
		*(shell->token) = new_token;
	else
		last_token->next = new_token;
}

char	*trim_quotes(char *word)
{
	char	*trimmed;
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = '\0';
	trimmed = ft_calloc((ft_strlen(word) + 1), sizeof(char));
	if (!trimmed)
		return (NULL);
	while (word[i])
	{
		if ((word[i] == '\'' || word[i] == '"') && (!quote || quote == word[i]))
			quote = word[i++];
		else
			trimmed[j++] = word[i++];
	}
	return (trimmed);
}
