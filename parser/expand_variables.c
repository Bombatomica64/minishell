/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/18 10:31:02 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*replace_str(char *original, char *to_repl, char *subs, int start)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_strndup(original, start);
	if (ft_strlen(subs) > 0)
		new = ft_strjoin_2free(new, subs);
	new = ft_newstrjoin(new, &original[start + ft_strlen(to_repl)]);
	return (free(to_repl), free(original), new);
}

char	*expand_dollar(char *str, char *tmp, size_t *i, t_data *data)
{
	char		*tofind;
	size_t		j;

	j = *i;
	tofind = NULL;
	if (tmp[*i + 1] == '\0')
		return (join_char(str, tmp[*i]));
	if (tmp[*i + 1] == '$' || tmp[*i + 1] == '!')
		return ((*i)++, str);
	else if (ft_isquote(tmp[*i + 1]))
		return (str);
	else if (tmp[((*i)++) + 1] == '?')
		return (ft_strjoin_2free(str, ft_itoa(data->error_codes)));
	else
	{
		while (ft_isalpha(tmp[j + 1])
			&& (ft_isalnum(tmp[(*i)]) || tmp[*i] == '_'))
			tofind = join_char(tofind, tmp[(*i)++]);
		tofind = join_char(tofind, '=');
		if (find_in_env(data->envp, tofind) != -1)
			str = ft_strjoin_2free(str, get_env_value(data->envp, tofind));
	}
	return (free(tofind), (*i)--, str);
}

char	*expand_dollar2(char *str, char *tmp, size_t *i, t_data *data)
{
	char	*tofind;
	size_t	j;

	j = *i;
	tofind = NULL;
	if (tmp[*i + 1] == '\0')
		return (join_char(str, tmp[*i]));
	if (tmp[*i + 1] == '$' || tmp[*i + 1] == '!')
		return ((*i)++, str);
	else if (tmp[((*i)++) + 1] == '?')
		return (ft_strjoin_2free(str, ft_itoa(data->error_codes)));
	else
	{
		while (ft_isalpha(tmp[j + 1])
			&& (ft_isalnum(tmp[(*i)]) || tmp[*i] == '_'))
			tofind = join_char(tofind, tmp[(*i)++]);
		if (!tofind)
			return (join_char(str, '$'));
		tofind = join_char(tofind, '=');
		if (find_in_env(data->envp, tofind) != -1)
			str = ft_strjoin_2free(str, get_env_value(data->envp, tofind));
	}
	return (free(tofind), (*i)--, str);
}

char	*ft_hereskip(char *str, char *tmp, size_t *i, t_quote *quote)
{
	str = join_char(str, tmp[(*i)++]);
	str = join_char(str, tmp[(*i)++]);
	while (tmp[*i] && ft_isspace(tmp[*i]))
		str = join_char(str, tmp[(*i)++]);
	while (tmp[*i] && (ft_isspace(tmp[*i]) == FALSE || (*quote).open == TRUE))
	{
		quote_start(&(*quote).open, tmp[*i], &(*quote).type);
		str = join_char(str, tmp[(*i)++]);
	}
	(*i)--;
	return (str);
}

char	*expand_name(char *tmp, t_data *data)
{
	size_t		i;
	char		*str;
	t_quote		quote;

	quote = (t_quote){0, 0};
	i = 0;
	str = NULL;
	if (!tmp)
		return (NULL);
	while ((tmp)[i] && (i < ft_strlen(tmp)))
	{
		quote_start(&quote.open, tmp[i], &quote.type);
		if (tmp[i] == '<' && tmp[i + 1] == '<' && quote.open == FALSE)
			str = ft_hereskip(str, tmp, &i, &quote);
		else if (tmp[i] == '$' && quote.type != '\'' && quote.open == FALSE)
			str = expand_dollar(str, tmp, &i, data);
		else if (tmp[i] == '$' && quote.type != '\'' && quote.open == TRUE)
			str = expand_dollar2(str, tmp, &i, data);
		else
			str = join_char(str, tmp[i]);
		i++;
	}
	str = ft_strtrimfree(str, "\t\n\v\f\r ", NULL);
	free(tmp);
	return (str);
}
/* 
void	expand_list(t_data *data)
{
	while ((data->input)->type != FINISH)
	{
		if ((data->input)->node && (data->input)->type != HEREDOC)
			(data->input)->node = expand_name((data->input)->node, data);
		data->input = (data->input)->next;
	}
	data->input = ft_inputfirst(&(data->input));
}
 */
