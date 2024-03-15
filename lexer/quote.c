/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:44:04 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/14 11:05:01 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	uselss_quotes(char **buff, char *quote)
{
	int		first_quote_index;
	char	*tmp;
	char	*tmp2;

	tmp = read_quotes(quote);
	if (!tmp)
		return ;
	tmp2 = ft_strjoin(*buff, tmp);
	free(*buff);
	*buff = tmp2;
	first_quote_index = find_first(tmp, *quote);
	if (first_quote_index != -1)
	{
		*quote = tmp[first_quote_index];
		uselss_quotes(buff, quote);
	}
	free(tmp);
	free(tmp2);
}

/* 
int	find_first(char *str, char c)
{
	char	*ptr;

	ptr = ft_strchr(str, c);
	if (ptr)
		return (ptr - str);
	else
		return (-1);
} */

char	*read_quotes(char *c)
{
	char	*tmp;

	tmp = NULL;
	if (*c == '\'')
		tmp = readline("quote> ");
	else if (*c == '\"')
		tmp = readline("dquote> ");
	if (!tmp)
		return (NULL);
	tmp = ft_strjoin_2("\n", tmp);
	return (tmp);
}

void	process_buff(char **line, char *buff, char quote)
{
	*line = strjoin_n_free1(*line, buff, find_first(buff, quote) + 1);
	if ((int)ft_strlen(buff) > find_first(buff, quote)
		&& open_quote_check(&buff[find_first(buff, quote) + 1], &quote) == TRUE)
		uselss_quotes(&buff, &quote);
	else
		free(buff);
}

void	handle_quote(char **line, char quote)
{
	int		in_quote;
	char	*buff;

	in_quote = FALSE;
	while (quote != 0)
	{
		buff = read_quotes(&quote);
		if (find_first(buff, quote) != -1)
		{
			in_quote = FALSE;
			break ;
		}
		else
			*line = ft_strjoin_2free(*line, buff);
	}
	if (in_quote == FALSE)
	{
		process_buff(line, buff, quote);
	}
}

void	quote_check(char **line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\'' || (*line)[i] == '\"')
		{
			if (quote == 0)
				quote = (*line)[i];
			else if (quote == (*line)[i])
				quote = 0;
		}
		i++;
	}
	if (quote != 0)
	{
		printf("quote: %c\n", quote);
		handle_quote(line, quote);
	}
}
