/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotehandler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:27:46 by sgarigli          #+#    #+#             */
/*   Updated: 2024/02/21 17:44:38 by sgarigli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_start(t_bool *quote, char c, char *quote_type, char **tmp)
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
	else if (*quote == TRUE)
		*tmp = join_char(*tmp, c);
}

void	quote_waiting(char **tmp, t_bool *quote, char *quote_type, t_type type)
{
	while (*quote == TRUE)
	{
		//quote_display(quote_type);
		if (type == COMMAND || type == BUILT_IN)
		{
			printf("quote> ");
		}
		else if (type == HEREDOC)
		{
			printf("heredoc> ");
		}
		else if (type == INPUT)
		{
			*tmp = ft_strjoin(*tmp, readline("\033[0;34mquote> \033[0m"));
		}
		else if (type == APPEND)
		{
			printf("append> ");
		}
		else if (type == TRUNC)
		{
			printf("trunc> ");
		}
		if (check_quote(*tmp, *quote_type) == TRUE)
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

t_bool	check_quote(char *tmp, char quote_type)
{
	int	i;
	int	quote_count;

	quote_count = 0;
	i = 0;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == quote_type)
			quote_count++;
		i++;
	}
	if (quote_count % 2 == 1)
		return (TRUE);
	return (FALSE);
}
