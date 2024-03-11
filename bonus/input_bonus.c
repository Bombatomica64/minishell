/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:46:56 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/11 17:01:50 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

t_bool	bonus_checker(char *line, t_data *data)
{
	t_quote	quote;
	int		i;

	i = skip_spaces2(line);
	quote = (t_quote){FALSE, 0};
	if (ft_isinset(line[i], "|&") > 0)
		return (lexer_error("syntax error near unexpected token: ",
				data, line[i]));
	i = ft_strlen(line) - 1;
	while (i >= 0)
	{
		quote_start(&quote.open, line[i], &quote.type);
		if (ft_isspace(line[i]) == TRUE && quote.open == FALSE)
			i--;
		else if (quote.open == TRUE)
			break ;
		else if (ft_isinset(line[i], "|&") > 0)
			return (lexer_error("syntax error near unexpected token: ",
					data, line[i]));
	}
	while (line[i] && line[i + 1] != '\0')
	{
		quote_start(&quote.open, line[i], &quote.type);
		if (quote.open == FALSE && ((line[i] && line[i + 1] == '&')
				|| (line[i] && line[i + 1] == '|')))
		{
			if (line[i + 2] && ft_isspace(line[i + 2]) == FALSE)
				return (lexer_error("syntax error near unexpected token",
						data, line[i + 2]));
		}
	}
}
