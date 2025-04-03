/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:19:39 by csalazar          #+#    #+#             */
/*   Updated: 2025/04/03 09:46:26 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	isseparator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	append_token(t_token **token, char *data, t_token_type type,
		t_shell *shell)
{
	t_token	*curr_token;
	t_token	*last_token;
	t_token	*new_token;

	curr_token = *token;
	if (!curr_token)
		last_token = NULL;
	else
	{
		while (curr_token->next)
			curr_token = curr_token->next;
		last_token = curr_token;
	}
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
		*token = new_token;
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
		{
			quote = word[i];
			i++;
		}
		else
		{
			trimmed[j] = word[i];
			i++;
			j++;
		}
	}
	return (trimmed);
}
