/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:44:04 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/01 17:11:53 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	uselss_quotes(char **buff, char *quote)
{
	char	*tmp;
	char	*tmp2;

	tmp = read_quotes(quote);
	if (!tmp)
		return ;
	tmp2 = ft_strjoin(*buff, tmp);
	free(*buff);
	*buff = tmp2;
	if (find_first(tmp, *quote) != -1)
		uselss_quotes(buff, quote);
	free(tmp);
	free(tmp2);
}

char	*strjoin_n_free1(char *line, char *buff, int index)
{
	int		i;
	int		new_str_len;
	char	*new_str;

	i = 0;
	new_str_len = ft_strlen(line) + index;
	new_str = malloc(ft_strlen(line) + index + 1);
	if (new_str)
	{
		while (line[i])
		{
			new_str[i] = line[i];
			i++;
		}
		while (i < new_str_len)
		{
			new_str[i] = buff[i - ft_strlen(line)];
			i++;
		}
		new_str[new_str_len] = '\0';
	}
	free(line);
	return (new_str);
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

int	find_first(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

t_bool	open_quote_check(char *line, char *new_quote)

{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (quote == 0)
				quote = line[i];
			else if (quote == line[i])
				quote = 0;
		}
		i++;
	}
	if (quote != 0)
	{
		*new_quote = quote;
		return (TRUE);
	}
	return (FALSE);
}

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

void	handle_quote(char **line, char quote)
{
	int		in_quote;
	char	*buff;

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
		*line = strjoin_n_free1(*line, buff,
				find_first(buff, quote) + 1);
		if ((int)ft_strlen(buff) > find_first(buff, quote)
			&& open_quote_check(&buff[find_first(buff, quote) + 1],
				&quote) == TRUE)
			uselss_quotes(&buff, &quote);
		else
			free(buff);
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
		handle_quote(line, quote);
	}
}
