/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:12:34 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/06 11:13:32 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_type	ft_file_type(char *str, int *j)
{
	if (str[*j] == '<')
	{
		(*j)++;
		if (str[*j] == '<')
		{
			(*j)++;
			return (HEREDOC);
		}
		else
			return (INPUT);
	}
	else if (str[*j] == '>')
	{
		(*j)++;
		if (str[*j] == '>')
		{
			(*j)++;
			return (APPEND);
		}
		else
			return (TRUNC);
	}
	else if (str[*j] == '|')
		(*j)++;
	return (COMMAND);
}

char	*join_char(char *str, char c)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!str)
	{
		tmp = malloc(sizeof(char) * 2);
		if (!tmp)
			return (NULL);
		tmp[0] = c;
		tmp[1] = '\0';
		return (tmp);
	}
	tmp = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = c;
	tmp[i + 1] = '\0';
	free(str);
	return (tmp);
}
//da fixare il caso < file1 grep e

int	count_limiter(char *str)
{
	int		i;
	int		count;
	t_bool	quote;
	char	quote_type;

	i = 0;
	quote = FALSE;
	count = 1;
	quote_type = '\0';
	i = skip_spaces2(str);
	if (!str)
		return (ERROR);
	if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
		i += 2;
	if (ft_islimiter(str[i]) == TRUE)
		i++;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote_start(&quote, str[i], &quote_type);
		if(((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>')) && quote == FALSE)
		{
			i += 2;
			count++;
		}
		if (ft_islimiter(str[i]) == TRUE && (quote == FALSE))
			count++;
		i++;
	}
	return (count);
}

char	*expand_dollar(char *str, char *tmp, size_t *i, t_data *data)
{
	char	*tofind;

	tofind = NULL;
	if (tmp[*i + 1] == '\0')
	{
		str = join_char(str, tmp[*i]);
		return (str);
	}
	else if (tmp[*i + 1] == '$' || tmp[*i + 1] == '?' || tmp[*i + 1] == '!')
	{
		(*i) += 1;
		return (str);
	}
	else
	{
		(*i)++;
		while (ft_isalnum(tmp[*i]) || tmp[*i] == '_')
		{
			tofind = join_char(tofind, tmp[*i]);
			(*i)++;
		}
		if (find_in_env(data->envp, tofind) != -1)
			str = ft_strjoin_2free(str, get_env_value(data->envp, tofind));
	}
	(*i)--;
	free(tofind);
	return (str);
}

char	*expand_variables(char *tmp, t_data *data, t_bool quote, char quote_type)
{
	size_t		i;
	char		*str;

	i = 0;
	str = NULL;
	while ((tmp)[i] && (i < ft_strlen(tmp)))
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
		{
			quote_start(&quote, tmp[i], &quote_type);
			str = join_char(str, tmp[i]);
		}
		else if (tmp[i] == '$' && quote_type != '\'')
			str = expand_dollar(str, tmp, &i, data);
		else
			str = join_char(str, tmp[i]);
		i++;
	}
	free(tmp);
	return (str);
}
