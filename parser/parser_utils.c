/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:12:34 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/27 17:26:12 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_type	ft_file_type(char *str, int *offset)
{
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
