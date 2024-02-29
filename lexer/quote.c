/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:44:04 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/29 18:40:37 by lmicheli         ###   ########.fr       */
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
	else
		free(tmp);
}

char	*strjoin_n_free1(char *line, char *buff, int index)
{
	int		line_len;
	int		new_str_len;
	char	*new_str;

	line_len = ft_strlen(line);
	new_str_len = line_len + index;
	new_str = malloc(ft_strlen(line) + index + 1);
	if (new_str)
	{
		if (line)
			strcpy(new_str, line);
		strncpy(new_str + line_len, buff, index);
		new_str[new_str_len] = '\0';
	}
	free(line);
	return (new_str);
}

int	find_first(char *str, char c)
{
	char	*ptr;

	ptr = ft_strchr(str, c);
	if (ptr)
		return (ptr - str);
	else
		return (-1);
}

t_bool	check_for_open_quote(char *line, char *quote)

{
	int		i;

	i = 0;
	*quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (*quote == 0)
				*quote = line[i];
			else if (*quote == line[i])
				*quote = 0;
		}
		i++;
	}
	if (*quote != 0)
		return (TRUE);
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
	return (tmp);
}

void	quote_check(char ***line)
{
	int		i;
	int		in_quote;
	char	quote;
	char	*buff;

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
		while (quote != 0)
		{
			buff = read_quotes(&quote);
			if (find_first(buff, quote) != -1)
				in_quote = TRUE;
			else
				buff = ft_strjoin_2free(*line, buff);
		}
		if (in_quote == TRUE)
		{
			*line = strjoin_n_free1(*line, buff,
					find_first(buff, quote));
			if (check_for_open_quote(&buff[find_first(buff, quote) + 1],
					&quote) == TRUE)
				uselss_quotes(&buff, &quote);
			else
				free(buff);
		}
	}
}
