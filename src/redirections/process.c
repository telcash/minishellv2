/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:25:30 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/28 17:11:45 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int process_input_redirections(t_token *token)
{
    int in;

    in = dup(STDIN_FILENO);
    while(token && token->type != PIPE)
    {
        if (token->type == IN)
            close(in);
        if (token->type == IN)
            in = process_in(token->data);
        token = token->next;
    }
    return (in);
}

int process_output_redirections(t_token *token)
{
    int out;

    out = STDOUT_FILENO;
    while(token && token->type != PIPE)
    {
        if (out != STDOUT_FILENO && (token->type == OUT || token->type == APPEND))
            close(out);
        if (token->type == OUT)
            out = process_out(token->data);
        else if (token->type == APPEND)
            out = process_append(token->data);
        token = token->next;
    }
    return (out);
}