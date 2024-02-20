/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:50:51 by mruggier          #+#    #+#             */
/*   Updated: 2024/02/20 11:27:42 by sgarigli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_spaces(char **str)
{
	while (**str == ' ' && **str != '\0')
		(*str)++;
}

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
	return (COMMAND); //check se e' un built in
}

t_bool	is_not_limiter(char c)
{
	if (c != '<' && c != '>' && c != '\0' && c != '|')
		return (TRUE);
	return (FALSE);
}

char	*get_name(char *str, int tmp_type)
{
	char	*tmp;
	int		i;
	t_bool	quote;
	char	c;
	char	quote_type;

	i = 0;
	quote = FALSE;
	quote_type = '\0';
	if (tmp_type == COMMAND || tmp_type == BUILT_IN)
	{
		while (is_not_limiter(str[i]))
		{
			if (str[i] == '\'' || str[i] == '\"')
				quote_start(&quote, &str[i], &quote_type);
			tmp[i] = str[i];
			i++;
		}
	}
	else
	{
		while (str[i] != ' ' && str[i] != '\0')
		{
			if (str[i] == '\'' || str[i] == '\"')
				quote_start(&quote, &str[i], &quote_type);
			else
				tmp[i] = str[i];
			i++;
		}
	}
	if (quote == TRUE)
		quote_waiting(&tmp, &quote, &quote_type, tmp_type);
	return (tmp);
}

void	ft_parser(char *str, t_data *data)
{
	char	*tmp;
	t_type	tmp_type;
	int		i;

	i = 0;
	skip_spaces(&str);
	tmp_type = ft_file_type(&str);
	tmp = get_name(&str, tmp_type);
	ft_inputadd_back(&(*data).input, ft_inputnew(tmp, tmp_type));
}
// Path: srcs/parser.c