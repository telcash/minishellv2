/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 22:53:40 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/21 14:47:26 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int tokenize_expansion(char *expanded, t_shell *shell)
{
	char **split;

	int i;

	split = ft_split(expanded, ' ');
	i = 0;
	while (split[i])
	{
		append_token(ft_strdup(split[i]), WORD, shell, 1);
		i++;
	}
	free_split(split);
	return (0);
}

static t_token	*get_last_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

void	append_token(char *data, t_token_type type, t_shell *shell, int is_exp)
{
	t_token	*curr_token;
	t_token	*last_token;
	t_token	*new_token;
	char *tmp;
	char *expanded;

	new_token = NULL;
	curr_token = *(shell->token);
	last_token = get_last_token(curr_token);
	if (last_token && last_token->type == HERE_DOC)
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return ;
		new_token->data = data;
	}
	else if (ft_strchr(data, '$'))
	{
		expanded = expand_line(data, shell);
		free(data);
		tokenize_expansion(expanded, shell);
		free (expanded);
	}
	else
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return ;
		tmp = expand_tilde(data, shell);
		if (!is_exp)
			new_token->data = trim_line_quotes(tmp);
		else
			new_token->data = ft_strdup(tmp);
		free(data);
		free(tmp);
	}
	if (new_token)
	{
		new_token->type = type;
		new_token->next = NULL;
		if (!last_token)
			*(shell->token) = new_token;
		else
			last_token->next = new_token;
	}
}
