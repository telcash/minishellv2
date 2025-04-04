/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:32:31 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/04/04 14:45:35 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ft_strjoin3(char *s1, char *s2, char *s3)
{
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    size_t len3 = ft_strlen(s3);
    char *result = malloc(len1 + len2 + len3 + 1);
    if (!result)
        return (NULL);
    ft_strlcpy(result, s1, len1 + 1);
    ft_strlcat(result, s2, len1 + len2 + 1);
    ft_strlcat(result, s3, len1 + len2 + len3 + 1);
    return (result);
}

int	len_2d_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (*arr)
	{
		arr++;
		i++;
	}
	return (i);
}