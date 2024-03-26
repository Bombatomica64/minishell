/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:40:43 by sgarigli          #+#    #+#             */
/*   Updated: 2024/03/26 10:44:17 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*expand_dollar(char *str, char *tmp, size_t *i, t_data *data)
{
	char	*tofind;

	tofind = NULL;
	if (tmp[*i + 1] == '\0')
		return (join_char(str, tmp[*i]));
	else if (tmp[*i + 1] == '$' || tmp[*i + 1] == '!')
		return ((*i)++, str);
	else if (tmp[*i + 1] == '?')
	{
		(*i)++;
		str = ft_strjoin_2free(str, ft_itoa(data->error_codes));
		return (str);
	}
	else if (!ft_isalnum(tmp[*i + 1]))
		return (join_char(str, tmp[*i]));
	else
	{
		(*i)++;
		while (ft_isalpha(tmp[0]) && (ft_isalnum(tmp[*i]) || tmp[*i] == '_'))
			tofind = join_char(tofind, tmp[(*i)++]);
		if (find_in_env(data->envp, tofind) != -1)
			str = ft_strjoin_2free(str, get_env_value(data->envp, tofind));
	}
	return (free(tofind), (*i)--, str);
}

char	*expand_name(char *tmp, t_data *data)
{
	size_t		i;
	char		*str;
	t_quote 	quote;

	quote = (t_quote){0, 0};
	i = 0;
	str = NULL;
	if (!tmp)
		return (NULL);
	while ((tmp)[i] && (i < ft_strlen(tmp)))
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
		{
			quote_start(&quote.open, tmp[i], &quote.type);
			str = join_char(str, tmp[i]);
		}
		else if (tmp[i] == '$' && quote.type != '\'')
			str = expand_dollar(str, tmp, &i, data);
		else
			str = join_char(str, tmp[i]);
		i++;
	}
	free(tmp);
	return (str);
}

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

void	expand_input(char **str, t_data *data)
{
	t_type	last_lim;
	t_quote	squote;
	int		i;

	i = 0;
	squote = (t_quote){FALSE, 0};
	last_lim = COMMAND;
	while ((*str)[i])
	{
		quote_start(&squote.open, (*str)[i], &squote.type);
		if ((ft_islimiter((*str)[i]) == TRUE && squote.open == FALSE))
			last_lim = ft_file_type((*str), i);
		if (last_lim == HEREDOC && (*str)[i] == ' ' && squote.open == FALSE)
			last_lim = COMMAND;
		if ((*str)[i] == '$' && squote.type != '\'' && last_lim != HEREDOC)
			*str = expand_first(str, i, data);
		i++;
	}
}
