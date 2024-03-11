/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:04:09 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/11 18:06:23 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_bool	check_if_last(char c, char *str, t_data *data)
{
	int		i;

	i = 0;
	if (str[i + 1] && str[i + 1] == c)
		i++;
	if (str[i + 1] && ft_islimiter(str[i + 1]))
		return (lexer_error(
				"Syntax error near unexpected token: ", data, str[i + 1]));
	while (str[i] && ft_isspace(str[i]) == TRUE)
		i++;
	if (str[i] == '\0')
		return (lexer_error(
				"Syntax error near unexpected token: ", data, c));
	else
		return (TRUE);
}

t_bool	redir_check(char *line, t_data *data)
{
	int		i;
	t_quote	quote;

	i = skip_spaces2(line);
	quote = (t_quote){FALSE, 0};
	while (line[i])
	{
		quote_start(&quote.open, line[i], &quote.type);
		if (quote.open == FALSE && ft_isinset(line[i], "<>") > 0)
			if (check_if_last(line[i], &line[i], data) == FALSE)
				return (FALSE);
		i++;
	}
	return (TRUE);
}
