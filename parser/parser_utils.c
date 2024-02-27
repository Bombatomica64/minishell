/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:12:34 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/27 11:14:21 by sgarigli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_type	ft_file_type(char **str)
{
	if (**str == '<')
	{
		(*str)++;
		if (**str == '<')
		{
			(*str)++;
			return (HEREDOC);
		}
		else
			return (INPUT);
	}
	else if (**str == '>')
	{
		(*str)++;
		if (**str == '>')
		{
			(*str)++;
			return (APPEND);
		}
		else
			return (TRUNC);
	}
	else if (**str == '|')
	{
		(*str)++;
		return (COMMAND);
	}
	return (COMMAND);
}

char	*join_char(char *str, char c)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!str)
	{
		tmp = malloc(sizeof(char) * 2);
		if (!tmp)
			return (NULL);
		tmp[0] = c;
		tmp[1] = '\0';
		return (tmp);
	}
	tmp = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = c;
	tmp[i + 1] = '\0';
	free(str);
	return (tmp);
}

int	count_limiter(char *str)
{
	int		i;
	int		count;
	t_bool	quote;
	char	quote_type;

	i = 0;
	quote = FALSE;
	count = 1;
	quote_type = '\0';
	skip_spaces(&str);
	if (!str)
		return (ERROR);
	if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
	{
		i += 2;
		count++;
	}
	if (ft_islimiter(str[i]) == TRUE)
	{
		i++;
		count++;
	}
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote_start(&quote, str[i], &quote_type);
		if(((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>')) && quote == FALSE)
		{
			i += 2;
			count++;
		}
		if (ft_islimiter(str[i]) == TRUE && (quote == FALSE))
			count++;
		i++;
	}
	printf("count = %d\n", count);
	return (count);
}
