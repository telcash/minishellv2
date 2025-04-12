/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:19:39 by csalazar          #+#    #+#             */
/*   Updated: 2025/04/12 09:49:53 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*append_word_segment(char *data, char *word, int start, int end)
{
	char	*tmp;
	char	*new_data;

	tmp = ft_substr(word, start, end - start);
	if (!tmp)
		return (data);
	if (!data)
		data = ft_strdup("");
	new_data = ft_strjoin(data, tmp);
	free(tmp);
	if (!new_data)
		return (data);
	free(data);
	return (new_data);
}

static char	*get_expanded_variable(int start, int end, char *word,
		t_shell *shell)
{
	char	*tmp1;
	char	*tmp2;

	if (end - start > 1)
	{
		tmp1 = ft_substr(word, start + 1, end - start - 1);
		tmp2 = get_env_value(shell, tmp1);
		free(tmp1);
		if (tmp2)
			return (ft_strdup(tmp2));
		else
			return (NULL);
	}
	else
		return (NULL);
}

static char	*add_expanded_variable(char *data, char *word, int *i,
		t_shell *shell)
{
	char	*exp_var;
	int		start;
	int		end;

	start = *i;
	if (word[start + 1] == '?')
	{
		exp_var = ft_itoa(shell->last_exit_status);
		*i += 2;
		end = start + 2;
	}
	else
	{
		end = start + 1;
		while (word[end] && (ft_isalnum(word[end]) || word[end] == '_'))
			end++;
		exp_var = get_expanded_variable(start, end, word, shell);
	}
	*i = end;
	if (exp_var)
	{
		data = append_word_segment(data, exp_var, 0, ft_strlen(exp_var));
		free(exp_var);
	}
	return (data);
}

char	*trim_quotes_and_expand(char *word, t_shell *shell)
{
	char	*data;
	char	quote;
	int		start;
	int		i;

	data = NULL;
	quote = '\0';
	i = 0;
	while (word[i])
	{
		start = i;
		while (word[i] && ((!quote && word[i] != '\'' && word[i] != '"')
				|| (quote && word[i] != quote)) && word[i] != '$')
			i++;
		data = append_word_segment(data, word, start, i);
		if (word[i] == '$')
			data = add_expanded_variable(data, word, &i, shell);
		else if ((word[i] == '\'' || word[i] == '"') && !quote)
			quote = word[i++];
		else if (word[i] == quote)
			quote = '\0';
		else
			i++;
	}
	return (data);
}
/* 
char* int_to_str(int n) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", n);
    return strdup(buf);
}

int get_last_exit() {
    // simulate $? value (in real use, store it globally or set it from shell)
    return 42;
}

size_t env_len(const char* p, int* adv) {
    int last = get_last_exit();
    if (*p == '?') {
        char* s = int_to_str(last);
        *adv = 1;
        size_t l = strlen(s);
        free(s);
        return l;
    }
    int i = 0;
    while (isalnum(p[i]) || p[i] == '_') i++;
    char* name = strndup(p, i);
    char* val = getenv(name);
    size_t l = val ? strlen(val) : 0;
    free(name);
    *adv = i;
    return l;
}

size_t parse_len(const char* p, int dq, int sq) {
    if (!*p) return 0;
    if (*p == '\'' && !dq) return parse_len(p + 1, dq, !sq);
    if (*p == '"' && !sq) return parse_len(p + 1, !dq, sq);
    if (*p == '$' && !sq) {
        int adv = 0;
        size_t l = env_len(p + 1, &adv);
        return l + parse_len(p + 1 + adv, dq, sq);
    }
    return 1 + parse_len(p + 1, dq, sq);
}

char* env_val(const char* p, int* adv) {
    int last = get_last_exit();
    if (*p == '?') {
        *adv = 1;
        return int_to_str(last);
    }
    int i = 0;
    while (isalnum(p[i]) || p[i] == '_') i++;
    *adv = i;
    char* name = strndup(p, i);
    char* val = getenv(name);
    char* out = val ? strdup(val) : strdup("");
    free(name);
    return out;
}

void build_str(const char* p, char* out, int* oi, int dq, int sq) {
    if (!*p) return;
    if (*p == '\'' && !dq) return build_str(p + 1, out, oi, dq, !sq);
    if (*p == '"' && !sq) return build_str(p + 1, out, oi, !dq, sq);
    if (*p == '$' && !sq) {
        int adv = 0;
        char* val = env_val(p + 1, &adv);
        strcpy(out + *oi, val);
        *oi += strlen(val);
        free(val);
        return build_str(p + 1 + adv, out, oi, dq, sq);
    }
    out[(*oi)++] = *p;
    return build_str(p + 1, out, oi, dq, sq);
}

char *trim_quotes_and_expand(char *word, t_shell *shell) 
{
	size_t len;
	char *out;
	int oi;

	if (!shell) return NULL;
    len = parse_len(word, 0, 0);
    out = malloc(len + 1);
    oi = 0;
    build_str(word, out, &oi, 0, 0);
    out[oi] = '\0';
    return (out);
} */