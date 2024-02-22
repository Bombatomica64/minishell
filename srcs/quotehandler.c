/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotehandler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:27:46 by sgarigli          #+#    #+#             */
/*   Updated: 2024/02/22 12:19:17 by sgarigli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_start(t_bool *quote, char c, char *quote_type)
{
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

void	quote_waiting(char **tmp, t_bool *quote, char *quote_type, t_type type)
{
	int	index;

	(void)type;
	index = ft_strlen(*tmp) - 1;
	while (*quote == TRUE)
	{
		*tmp = ft_strjoin(*tmp, readline("\033[0;34mquote> \033[0m"));
	if (check_quote(*tmp, *quote_type, type, index) == TRUE)
		*quote = FALSE;
	}
}

void	quote_display(char *quote_type)
{
	if (*quote_type == '\'')
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("d", 0);
		rl_redisplay();
	}
	else if (*quote_type == '\"')
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

t_bool	check_quote(char *tmp, char quote_type, t_type type, int index) 
{
	int	i;
	int	quote_count;

	quote_count = 1;
	if (type == COMMAND || type == BUILT_IN)
		quote_count++;
	i = index;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == quote_type && quote_count % 2 == 1)
			quote_count++;
		else if(tmp[i] == '\'' || tmp[i] == '\"')
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
