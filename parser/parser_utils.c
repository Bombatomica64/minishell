/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:12:34 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/22 11:55:56 by sgarigli         ###   ########.fr       */
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

t_bool	is_double_operator(char *str, int i, t_quote squote)
{
	return (((str[i] == '<' && str[i + 1] == '<')
			|| (str[i] == '>' && str[i + 1] == '>'))
		&& squote.type == FALSE);
}
