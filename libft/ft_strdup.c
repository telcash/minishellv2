/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:55:04 by dfernan3          #+#    #+#             */
/*   Updated: 2025/04/04 10:25:09 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*buffer;

	buffer = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, s, ft_strlen(s) + 1);
	return (buffer);
}
