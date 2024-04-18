/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/18 10:31:02 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

t_bool	check_start_b(char *line, int *i)
{
	*i = skip_spaces2(line);
	if (ft_isinset(line[*i], "|&") > 0)
		return (FALSE);
	return (TRUE);
}

t_bool	check_end_b(char *line, t_quote *quote, int *i)
{
	*i = ft_strlen(line) - 1;
	while (*i >= 0)
	{
		quote_start(&quote->open, line[*i], &quote->type);
		if (ft_isspace(line[*i]) == TRUE && quote->open == FALSE)
			(*i)--;
		else if (quote->open == TRUE)
			break ;
		else if (ft_isinset(line[*i], "|&") > 0)
			return (FALSE);
		(*i)--;
	}
	return (TRUE);
}

t_bool	check_middle_b(char *line, t_quote *quote, int *i)
{
	*i = 0;
	while (line[*i] && line[*i + 1] != '\0')
	{
		quote_start(&quote->open, line[*i], &quote->type);
		if (quote->open == FALSE && ((line[*i] && line[*i + 1] == '&')
				|| (line[*i] && line[*i + 1] == '|')))
		{
			if (line[*i + 2] && ft_isspace(line[*i + 2]) == FALSE)
				return (FALSE);
		}
		(*i)++;
	}
	return (TRUE);
}

t_bool	bonus_checker(char *line, t_data *data)
{
	t_quote	quote;
	int		i;

	quote = (t_quote){FALSE, 0};
	if (!check_start_b(line, &i))
		return (lexer_error("minishell: syntax error near unexpected token `",
				data, line[i]));
	if (!check_end_b(line, &quote, &i))
		return (lexer_error("minishell: syntax error near unexpected token `",
				data, line[i]));
	if (!check_middle_b(line, &quote, &i))
		return (lexer_error("minishell: syntax error near unexpected token `",
				data, line[i + 2]));
	return (TRUE);
}
