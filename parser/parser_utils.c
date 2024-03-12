/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:12:34 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/12 11:32:32 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_type	ft_file_type(char *str, int *offset)
{
	if (str[*offset] == '<')
	{
		(*offset)++;
		if (str[*offset] == '<')
		{
			(*offset)++;
			return (HEREDOC);
		}
		else
			return (INPUT);
	}
	else if (str[*offset] == '>')
	{
		(*offset)++;
		if (str[*offset] == '>')
		{
			(*offset)++;
			return (APPEND);
		}
		else
			return (TRUNC);
	}
	else if (str[*offset] == '|')
		(*offset)++;
	return (COMMAND);
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
	if ((str[i] == '<' && str[i + 1] == '<')
		|| (str[i] == '>' && str[i + 1] == '>'))
		i += 2;
	if (ft_islimiter(str[i]) == TRUE)
		i++;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote_start(&quote, str[i], &quote_type);
		if (((str[i] == '<' && str[i + 1] == '<')
				|| (str[i] == '>' && str[i + 1] == '>')) && quote == FALSE)
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
