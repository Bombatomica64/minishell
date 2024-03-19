/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:52:13 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/19 10:02:12 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_bool	lexer_error(char *error, t_data *data, char c)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(2, 1);
		printf("%s`", error);
		printf("%c'\n", c);
		free_close(&data, 1);
	}
	else
		waitpid(pid, &data->error_codes, 0);
	return (FALSE);
}

t_bool	lexer(char **line, t_data *data)
{
	if (ft_strlen(*line) == 0)
		return (TRUE);
	if (pipe_check(*line) == FALSE)
		return (lexer_error("Syntax error near unexpected token: ", data, '|'));
	pipe_count(*line, data);
	quote_check(line);
	if (redir_check(*line, data) == FALSE)
		return (FALSE);
	return (TRUE);
}

	// if (bonus_checker(*line, data) == FALSE)
	// 	return (FALSE);