/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:19:39 by csalazar          #+#    #+#             */
/*   Updated: 2025/04/16 13:14:51 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*trim_quotes_and_expand(char *word, t_shell *shell)
{
	char	*data;
	char	s_quote;
	char	d_quote;
	int		start;
	int		i;

	data = NULL;
	s_quote = '\0';
	d_quote = '\0';
	i = 0;
	while (word[i])
	{
		start = i;
		while (word[i] && ((word[i] != '\'' && word[i] != '"' && word[i] != '$')
					|| (word[i] == '$' && s_quote) || (word[i] == '\''
					&& d_quote) || (word[i] == '"' && s_quote)))
			i++;
		data = append_word_segment(data, word, start, i);
		if (word[i] == '$' && !s_quote)
			data = add_expanded_variable(data, word, &i, shell);
		else if ((word[i] == '\'' && !d_quote) || (word[i] == '"' && !s_quote))
			toggle_quote(word[i++], &s_quote, &d_quote);				
	}
	return (data);
}
