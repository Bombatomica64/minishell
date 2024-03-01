/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:52:13 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/01 10:28:46 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

	i = 0;
	i = skip_spaces2(line);
	if (line[i] && line[i] == '|')
		return (FALSE);
	i = ft_strlen(line) - 1;
	while (i >= 0 && ft_isspace(line[i]))
		i--;
	if (line[i] == '|')
		return (FALSE);
	return (TRUE);
}

t_bool	lexer(char **line, t_data *data)
{
	if (pipe_check(*line) == FALSE)
		return (lexer_error("Syntax error near unexpected token '|'\n", data));
	quote_check(line);
	return (TRUE);
}
