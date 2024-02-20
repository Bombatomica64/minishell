/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:12:34 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/20 12:13:01 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	ft_file_type(char **str)
{
	if (**str == '<')
	{
		(*str)++;
		if (**str == '<')
		{
			return (HEREDOC);
			(*str)++;
		}
		else
			return (INPUT);
	}
	else if (**str == '>')
	{
		(*str)++;
		if (**str == '>')
		{
			return (APPEND);
			(*str)++;
		}
		else
			return (TRUNC);
	}
	return (COMMAND);
}

void	quote_start(t_bool *quote, char c, char quote_type)
{
	if (quote_type == '\0')
	{
		quote_type = c;
		*quote = TRUE;
		return ;
	}
	if (c == quote_type)
	{
		if (*quote == FALSE)
			*quote = TRUE;
		else
			*quote = FALSE;
		quote_type = '\0';
	}
}
