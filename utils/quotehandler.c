/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotehandler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/18 10:31:02 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	quote_start(t_bool *quote, char c, char *quote_type)
{
	if (c != '\'' && c != '\"')
		return ;
	if (*quote == FALSE)
	{
		*quote = TRUE;
		*quote_type = c;
	}
	else if (*quote == TRUE && *quote_type == c)
	{
		*quote = FALSE;
		*quote_type = '\0';
	}
}

t_bool	check_quote(char *tmp, char quote_type, t_type type, int index)
{
	int	i;
	int	quote_count;

	(void)type;
	(void)index;
	quote_count = 0;
	i = 0;
	if (type != COMMAND && type != BUILT_IN)
		quote_count++;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == quote_type)
			quote_count++;
		else if (tmp[i] != quote_type && (tmp[i] == '\''
				|| tmp[i] == '\"') && quote_count % 2 == 0)
		{
			quote_type = tmp[i];
			quote_count++;
		}
		i++;
	}
	if (quote_count % 2 == 0)
		return (TRUE);
	return (FALSE);
}

t_bool	quote_error(char *tmp, t_bool *quote)
{
	if (*quote == TRUE)
	{
		perror("Error: quote not closed\n");
		free(tmp);
		return (TRUE);
	}
	return (FALSE);
}
