/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:40:43 by sgarigli          #+#    #+#             */
/*   Updated: 2024/03/20 10:03:19 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//echo $"USER" mi serve una variabile statica per le quote

char	*expand_dollar(char *str, char *tmp, size_t *i, t_data *data, int *off)
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
		*off += 2;
		str = ft_strjoin_2free(str, ft_itoa(data->error_codes));
		return (str);
	}
	else if (!ft_isalnum(tmp[*i + 1]))
		return (join_char(str, tmp[*i]));
	else
	{
		(*i)++;
		while (ft_isalnum(tmp[*i]) || tmp[*i] == '_')
			tofind = join_char(tofind, tmp[(*i)++]);
		if (find_in_env(data->envp, tofind) != -1)
			str = ft_strjoin_2free(str, get_env_value(data->envp, tofind));
		else
			*off += ft_strlen(tofind) + 1;
	}
	return (free(tofind), (*i)--, str);
}

char	*expand_name(char *tmp, t_data *data, t_bool open, char type, int *off)
{
	size_t		i;
	char		*str;

	i = 0;
	str = NULL;
	if (!tmp)
		return (NULL);
	while ((tmp)[i] && (i < ft_strlen(tmp)))
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
		{
			quote_start(&open, tmp[i], &type);
			str = join_char(str, tmp[i]);
		}
		else if (tmp[i] == '$' && type != '\'')
			str = expand_dollar(str, tmp, &i, data, off);
		else
			str = join_char(str, tmp[i]);
		i++;
	} 
	free(tmp);
	return (str);
}

//grep c<file1
