/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotehandler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:27:46 by sgarigli          #+#    #+#             */
/*   Updated: 2024/02/20 12:10:46 by sgarigli         ###   ########.fr       */
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

void	quote_waiting(char **tmp, t_bool *quote, char *quote_type, t_type tmp_type)
{
	while(*quote == TRUE)
	{
		quotedisplay(quote_type);
		if (tmp_type == COMMAND || tmp_type == BUILT_IN)
		{
			
		}
		else if (tmp_type == HEREDOC)
		{
			/* code */
		}
		else if (tmp_type == INPUT)
		{
			*tmp = ft_strjoin(tmp, readline("> "));
		}
		else if (tmp_type == APPEND)
		{
			/* code */
		}
		else if (tmp_type == TRUNC)
		{
			/* code */
		}
		if (checkquote(*tmp, *quote_type) == TRUE)
			*quote = FALSE;
	}
}

void	quotedisplay(char *quote_type)
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
 // Doesn't check correctly
t_bool	checkquote(char *tmp, char quote_type)
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
