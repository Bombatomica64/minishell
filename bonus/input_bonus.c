/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:46:56 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/22 16:14:12 by mruggier         ###   ########.fr       */
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
