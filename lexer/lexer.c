/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:52:13 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/25 10:10:22 by sgarigli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_bool	lexer_error(char *error, t_data *data, char c)
{
	data->error_codes = 2;
	ft_putstr_fd(error, 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	return (FALSE);
}

t_bool	lexer(char **line, t_data *data)
{
	if (ft_strlen(*line) == 0)
		return (TRUE);
	if (pipe_check(*line) == FALSE)
		return (lexer_error("minishell: syntax error near unexpected token `", data, '|'));
	pipe_count(*line, data);
	quote_check(line);
	if (redir_check(*line, data) == FALSE)
		return (FALSE);
	return (TRUE);
}

	// if (bonus_checker(*line, data) == FALSE)
	// 	return (FALSE);