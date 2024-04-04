/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:12:34 by mruggier          #+#    #+#             */
/*   Updated: 2024/04/04 11:44:41 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*remove_quotes(char *str, int *offset)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*new;

	i = get_cmd_name(str, offset, (t_quote){FALSE, 0});
	tmp = ft_substr(str, 0, i);
	tmp2 = ft_strncpy_noquote(tmp, 0, ft_strlen(tmp), (t_quote){FALSE, 0});
	free(tmp);
	new = ft_strdup(str + i);
	free(str);
	str = ft_strjoin_2free(tmp2, new);
	return (str);
}

int	get_cmd_name(char *str, int *offset, t_quote squote)
{
	int	i;

	i = *offset;
	while (str[i])
	{
		quote_start(&squote.open, str[i], &squote.type);
		if (squote.open == FALSE && ft_isspace(str[i]) == TRUE)
			break ;
		i++;
	}
	*offset = i;
	return (i);
}

t_type	ft_file_type(char *str, int *offset)
{
	*offset = skip_spaces2(str);
	if (str[*offset] == '<')
	{
		(*offset)++;
		if (str[*offset] == '<')
			return ((*offset)++, HEREDOC);
		else
			return (INPUT);
	}
	else if (str[*offset] == '>')
	{
		(*offset)++;
		if (str[*offset] == '>')
			return ((*offset)++, APPEND);
		else
			return (TRUNC);
	}
	else if (str[*offset] == '|')
		return ((*offset)++, PIPPE);
	return (COMMAND);
}

int	count_limiter(char *str, t_quote squote)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	i = skip_spaces2(str);
	if (!str)
		return (ERROR);
	if (is_double_operator(str, i, squote) == TRUE)
		i += 2;
	if (ft_islimiter(str[i]) == TRUE)
		i++;
	while (str[i])
	{
		quote_start(&squote.open, str[i], &squote.type);
		if (is_double_operator(str, i, squote) == TRUE)
		{
			i += 2;
			count++;
		}
		if (ft_islimiter(str[i]) == TRUE && (squote.type == FALSE))
			count++;
		i++;
	}
	return (count);
}

int	i_skip_pippe(char *str, int i)
{
	i = 0;
	while (str[i] == '|' || ft_isspace(str[i]) == TRUE)
		i++;
	return (i);
}

char	*cut_pars_str(char *str, char *node)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == node[0])
		{
			j = 0;
			while (node[j] && node[j] == str[i + j])
				j++;
			if (!node[j])
				return (cut_string(i + j,
						ft_strtrimfree(str, " \t\r\n\v\f", 0)));
		}
		i++;
	}
	return (free(str), NULL);
}
