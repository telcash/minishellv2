/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:36:40 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/03/29 11:39:33 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char    *ft_get_next_line(void)
{
    char    buffer[2];
    int     ret;
    char    *tmp;
    char    *line;

    line = ft_strdup("");
    ret = 1;
    buffer[0] = '\0';
    while (buffer[0] != '\n' && ret > 0)
    {
        ret = read(STDIN_FILENO, buffer, 1);
        buffer[1] = '\0';
        tmp = line;
        line = ft_strjoin(line, buffer);
        free(tmp);
    }
    return (line);
}

int process_here_doc(char *delimiter)
{
    char *line;
    int     out;

    out = open("/tmp/.here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (out == -1)
        return (perror("open"), -1);
    line = ft_get_next_line();
    while (line)
    {
        if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
        {
            free(line);
            close(out);
            out = open("/tmp/.here_doc", O_RDONLY);
            if (out == -1)
                return (perror("open"), -1);
            return (out);
        }
        write(out, line, ft_strlen(line));
        free(line);
        line = get_next_line(STDIN_FILENO);
    }
    return (0);
}
