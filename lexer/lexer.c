/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:52:13 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/04 10:58:45 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

t_bool	lexer_error(char *error, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(2, 1);
		ft_printf("%s", error);
		data->error_codes = 2;
	}
	else
		waitpid(pid, &data->error_codes, 0);
	return (FALSE);
}

t_bool	pipe_check(char *line)
{
	int		i;

	i = skip_spaces2(line);
	if (line[i] && line[i] == '|')
		return (FALSE);
	i = ft_strlen(line) - 1;
	while (i > 0 && ft_isspace(line[i]))
		i--;
	if (line[i] == '|')
		return (FALSE);
	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
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

t_bool	lexer(char **line, t_data *data)
{
	if (ft_strlen(*line) == 0)
		return (TRUE);
	if (pipe_check(*line) == FALSE)
		return (lexer_error("Syntax error near unexpected token '|'\n", data));
	pipe_count(*line, data);
	quote_check(line);
	return (TRUE);
}
