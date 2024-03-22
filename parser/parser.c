/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:11:17 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/22 15:31:56 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	get_name(char *str, t_parser *parser, t_data *data, int *off)
{
	t_bool		check;

	check = TRUE;
	if (parser->tmp_type == COMMAND || parser->tmp_type == BUILT_IN)
		check = get_command(off, str, parser, data);
	else if (parser->tmp_type == HEREDOC || parser->tmp_type == INPUT
		|| parser->tmp_type == APPEND || parser->tmp_type == TRUNC)
		check = get_inout(off, str, parser, data);
	return (check);
	// {
	// 	quote_start(&quote->open, str[i], &quote->type);
	// 	while (str[i] && ft_isspace(str[i]) == FALSE && ft_islimiter(str[i]) == FALSE && quote->open == FALSE)
	// 	{
	// 		tmp = join_char(tmp, str[i]);
	// 		i++;
	// 	}
	// 	if (tmp_type != HEREDOC)
	// 		tmp = expand_name(tmp, data, quote->open, quote->type, off);
	// 	return (tmp);
	// }
	// while (str[i] != 0)
	// {
	// 	if (ft_isquote(str[i]))
	// 	{
	// 		quote_start(&quote->open, str[i], &quote->type);
	// 		if (tmp_type == BUILT_IN || tmp_type == COMMAND
	// 			|| (quote->open == TRUE && str[i] != quote->type))
	// 			tmp = join_char(tmp, str[i]);
	// 		i++;
	// 	}
	// 	else
	// 	{
	// 		tmp = join_char(tmp, str[i]);
	// 		i++;
	// 	}
	// 	if (ft_islimiter(str[i]) == TRUE && quote->open == FALSE)
	// 		break ;
	// }
	// if (tmp_type != HEREDOC)
	// 	tmp = expand_name(tmp, data, quote->open, quote->type, off);
	// return (tmp);
}

char	*get_path(char **tmp, t_type tmp_type, t_data *data, int *offset)
{
	char	*tmp_path;
	int		i;
	int		j;

	tmp_path = NULL;
	i = 0;
	if (*tmp == NULL)
		return (NULL);
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

char	*cut_pars_str(char *str, char *node)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == node[0])
		{
			j = 0;
			while (node[j] && node[j] == str[i + j])
				j++;
			if (!node[j])
				return (cut_string(i + j, str));
		}
		i++;
	}
	return (free(str), NULL);
}

t_bool	parser(char *str, t_data *data, int offset, t_parser parser)
{
	t_quote		quote;
	int			check;

	quote = (t_quote){FALSE, 0};
	str = expand_name(str, data, quote, &offset);
	while (str)
	{
		offset = skip_spaces2(str);
		parser.tmp_type = ft_file_type(str, &offset);
		check = get_name(str, &parser, data, &offset);
		if (check == FALSE)
		{
			str = ft_reparsing(str, offset, data, (t_quote){FALSE, 0});
			free_parser(&parser);
			offset = 0;
			check = TRUE;
			continue ;
		}
		offset += skip_spaces2(str + offset);
		parser.tmp = ft_strtrimfree(parser.tmp, " \t\r\n\v\f", &offset);
		if (ft_isbuiltin(parser.tmp) == TRUE)
			parser.tmp_type = BUILT_IN;
		parser.tmp_path = get_path(&parser.tmp, parser.tmp_type, data, &offset);
		if (parser.tmp_path == NULL && (parser.tmp_type <= 1026))
			return (free(parser.tmp), free(str), FALSE);
		ft_inputadd_back(&data->input, ft_inputnew(parser));
		//printf("offset =%d\tparser.tmp = %s\tstrlen = %ld\n", offset,parser.tmp, ft_strlen(parser.tmp));
		// str = cut_string(offset + ft_strlen(parser.tmp), str);
		str = cut_pars_str(str, parser.tmp);
		free_parser(&parser);
	}
	ft_inputadd_back(&data->input, ft_inputnew((t_parser){NULL, NULL, 69}));
	free(str);
	//print_list(data->input);
	return (TRUE);
}
// Path: srcs/parser.c
//ptr[32, | , 3 ,4]