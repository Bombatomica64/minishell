/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:08:44 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/14 18:43:52 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_bool	check_start_end(char *line, t_quote *squote)
{
	int	i;

	i = skip_spaces2(line);
	quote_start(&squote->open, line[i], &squote->type);
	if (line[i] && line[i] == '|')
		return (FALSE);
	i = ft_strlen(line) - 1;
	while (i > 0 && ft_isspace(line[i]))
		i--;
	if (line[i] == '|')
		return (FALSE);
	return (TRUE);
}

t_bool	check_middle(char *line, t_quote *squote)
{
	int	i;

	i = 0;
	while (line[i])
	{
		quote_start(&squote->open, line[i], &squote->type);
		if (line[i] == '|' && squote->open == FALSE)
		{
			i++;
			i += skip_spaces2(&line[i]);
			if (line[i] == '|')
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

t_bool	pipe_check(char *line)
{
	t_quote	squote;

	squote = (t_quote){FALSE, 0};
	if (!check_start_end(line, &squote))
		return (FALSE);
	if (!check_middle(line, &squote))
		return (FALSE);
	return (TRUE);
}

int	pipe_count(char *line, t_data *data)
{
	int		i;
	int		pipe_count;
	char	quote;

	i = 0;
	pipe_count = 0;
	quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (quote == 0)
				quote = line[i];
			else if (quote == line[i])
				quote = 0;
		}
		if (line[i] == '|' && quote == 0)
			pipe_count++;
		i++;
	}
	data->pipe_nbr = pipe_count;
	return (pipe_count);
}
