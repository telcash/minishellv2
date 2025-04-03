/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 22:39:16 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/03 07:31:43 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int is_redirection(t_token *token)
{
    return (token->type == IN || token->type == OUT || token->type == HERE_DOC
            || token->type == APPEND);
}

static int verify_next_token_to_redirection(t_token *token)
{
    if (!token->next)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
        return (1);
    }
    if (is_redirection(token->next ) || token->next->type == PIPE)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
        ft_putchar_fd(token->next->data[0], 2);
        ft_putstr_fd("'\n", 2);
        return (1);
    }
    return (0);
}

static int verify_next_token_to_pipe(t_token *token)
{
    if (!token->next)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
        return (1);
    }
    if (token->next->type == PIPE)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
        return (1);
    }
    return (0);
}

static void set_redir_token_data(t_token *token)
{
    t_token *next_token;

    next_token = token->next;
    token->data = next_token->data;
    token->next = next_token->next;
}

int verify_token(t_token **token)
{
    t_token *tmp;

    tmp = *token;
    if (!tmp)
        return (1);
    if (tmp->type == PIPE && !tmp->next)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
        return (1);
    }
    while (tmp)
    {
        if (tmp->type == PIPE && verify_next_token_to_pipe(tmp))
            return (1);
        if (is_redirection(tmp) && verify_next_token_to_redirection(tmp))
            return (1);
        if (is_redirection(tmp))
            set_redir_token_data(tmp);
        tmp = tmp->next;
    }
    return (0);
}
