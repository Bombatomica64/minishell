/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:40:43 by sgarigli          #+#    #+#             */
/*   Updated: 2024/03/26 10:55:19 by gduranti         ###   ########.fr       */
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
		tofind =  join_char(tofind, '=');
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

char	*expand_first(char *str, int *i, t_data *data)
{
	char	*dst;
	char	*tofind;
	char	*tmp;
	int		j;

	j = 0;
	tmp = NULL;
	while (str[++(*i)] && ft_isalnum(str[(*i)]))
		j++;
	tofind = join_char(ft_strncpy(str, (*i) - j, *i), '=');
	if (find_in_env(data->envp, tofind) != -1)
			tmp = get_env_value(data->envp, tofind);
	dst = ft_strncpy(str, 0, (*i) - j);
	dst = ft_newstrjoin(dst, tmp);
	dst = ft_newstrjoin(dst, &str[*i]);
	*i = *i - j + ft_strlen(tmp);
	return (free(str), free(tofind), free(tmp), dst);
}
