/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 22:53:40 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/06 22:54:01 by carlossalaz      ###   ########.fr       */
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
	new_token->data = data;
	new_token->type = type;
	new_token->next = NULL;
	if (!last_token)
		*(shell->token) = new_token;
	else
		last_token->next = new_token;
}