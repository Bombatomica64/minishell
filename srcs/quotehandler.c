/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotehandler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:27:46 by sgarigli          #+#    #+#             */
/*   Updated: 2024/02/20 16:08:25 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_start(t_bool *quote, char c, char *quote_type)
{
	if (*quote_type == '\0')
	{
		*quote_type = c;
		*quote = TRUE;
		return ;
	}
	if (c == *quote_type)
	{
		if (*quote == FALSE)
			*quote = TRUE;
		else
			*quote = FALSE;
		quote_type = '\0';
	}
}

void	quote_waiting(char **tmp, t_bool *quote, char *quote_type, t_type type)
{
	while (*quote == TRUE)
	{
		quote_display(quote_type);
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
			*tmp = ft_strjoin(*tmp, readline("> "));
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
		rl_replace_line("quote", 0);
		rl_redisplay();
	}
	else if (*quote_type == '\"')
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("dquote", 0);
		rl_redisplay();
	}
}

t_bool	check_quote(char *tmp, char quote_type)
{
	int	i;

	i = 0;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == quote_type)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
