/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:11:17 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/19 11:06:19 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_name(char *str, int tmp_type, t_quote *quote, t_data *data, int *off)
{
	int			i ;
	char		*tmp;

	i = 0;
	tmp = NULL;
	i = skip_spaces2(str);
	if (tmp_type == HEREDOC || tmp_type == INPUT
		|| tmp_type == APPEND || tmp_type == TRUNC)
	{
		quote_start(&quote->open, str[i], &quote->type);
		while (str[i] && ft_isspace(str[i]) == FALSE && quote->open == FALSE)
		{
			tmp = join_char(tmp, str[i]);
			i++;
		}
		if (tmp_type != HEREDOC)
			tmp = expand_name(tmp, data, quote->open, quote->type, off);
		return (tmp);
	}
	while (str[i] != 0)
	{
		if (ft_isquote(str[i]))
		{
			quote_start(&quote->open, str[i], &quote->type);
			if (tmp_type == BUILT_IN || tmp_type == COMMAND
				|| (quote->open == TRUE && str[i] != quote->type))
				tmp = join_char(tmp, str[i]);
			i++;
		}
		else
		{
			tmp = join_char(tmp, str[i]);
			i++;
		}
		if (ft_islimiter(str[i]) == TRUE && quote->open == FALSE)
			break ;
	}
	if (tmp_type != HEREDOC)
		tmp = expand_name(tmp, data, quote->open, quote->type, off);
	return (tmp);
}

char	*get_path(char **tmp, t_type tmp_type, t_data *data, int *offset)
{
	char	*tmp_path;
	int		i;
	int		j;

	tmp_path = NULL;
	i = 0;
	if (tmp_type == COMMAND)
	{
		while ((*tmp)[i] != ' ' && (*tmp)[i] != '\0')
		{
			if (ft_isquote((*tmp)[i]) == TRUE)
			{
				i++;
				j = i;
				while ((*tmp)[j] != '\'' && (*tmp)[j] != '\"')
					j++;
				tmp_path = ft_strjoin_2free(tmp_path,
						ft_strncpy_noquote(*tmp, i, j));
				i = j;
			}
			else
				tmp_path = join_char(tmp_path, (*tmp)[i]);
			i++;
		}
		if (ft_strchr(tmp_path, '/') == NULL && tmp_type != BUILT_IN)
		{
			tmp_path = path_execve(tmp_path, data->envp);
			if (tmp_path == NULL)
			{
				free(tmp_path);
				return (ft_error(*tmp, NO_PATH, 127, data), NULL);
			}
		}
		else if (tmp_type != BUILT_IN && find_first(tmp_path, '/') != -1)
		{
			*offset += find_last(*tmp, '/') + 1;
			*tmp = cut_string(find_last(*tmp, '/') + 1, *tmp);
		}
	}
	else if (tmp_type != HEREDOC)
		tmp_path = refactor_path(*tmp, data, 0, offset);
	return (tmp_path);
}

char	*free_strdup(char *str, char **freestr)
{
	char	*tmp;

	tmp = ft_strdup(str);
	free(*freestr);
	return (tmp);
}

t_bool	parser(char *str, t_data *data, int offset)
{
	t_quote		quote;
	t_parser	parser;

	quote = (t_quote){FALSE, 0};
	while (str)
	{
		offset = skip_spaces2(str);
		parser.tmp_type = ft_file_type(str, &offset);
		parser.tmp = get_name(str + offset,
				parser.tmp_type, &quote, data, &offset);
		printf("offset prima trim: %d\n", offset);
		parser.tmp = ft_strtrimfree(parser.tmp, " \t\r\n\v\f", &offset);
		printf("offset dopo trim: %d\n", offset);
		if (ft_isbuiltin(parser.tmp) == TRUE)
			parser.tmp_type = BUILT_IN;
		parser.tmp_path = get_path(&parser.tmp, parser.tmp_type, data, &offset);
		if (parser.tmp_path == NULL && (parser.tmp_type <= COMMAND))
			return (free(parser.tmp), free(str), FALSE);
		ft_inputadd_back(&(*data).input, ft_inputnew(parser));
		printf("offset: %d\n", offset);
		str = cut_string(offset + ft_strlen(parser.tmp), str);
		free(parser.tmp);
		free(parser.tmp_path);
	}
	ft_inputadd_back(&(*data).input, ft_inputnew((t_parser){NULL, NULL, 69}));
	free(str);
	return (TRUE);
}
// Path: srcs/parser.c
//ptr[32, | , 3 ,4]