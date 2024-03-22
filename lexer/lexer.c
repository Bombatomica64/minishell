/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:52:13 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/22 15:16:42 by mruggier         ###   ########.fr       */
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

t_bool	file_check(char *line, t_data *data)
{
	struct stat st;

	//printf("line: %s\n", line);
	if (strncmp(line, "./", 2) == 0 || strncmp(line, "/", 1) == 0)
    {
		if (stat(line, &st) == -1)
		{
			ft_error(line, NO_EXST, 127, data);
			return (FALSE);
		}
		else if (S_ISDIR(st.st_mode))
		{
			ft_error(line, DIR, 126, data);
			return (FALSE);
		}
		else if (access(line, X_OK) == -1)
        {
            ft_error(line, ACCESS, 126, data);
            return (FALSE);
        }
	}
	return (TRUE);
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
	if (file_check(*line, data) == FALSE)
		return (FALSE);
	return (TRUE);
}

	// if (bonus_checker(*line, data) == FALSE)
	// 	return (FALSE);