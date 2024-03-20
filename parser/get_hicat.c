/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hicat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:05:27 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/20 18:00:02 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	get_command(int *off, char *str, t_parser *parser, t_data *data)
{
	int		i;
	t_quote	squote;

	i = 0;
	squote = (t_quote){FALSE, 0};
	printf("parser->tmp: %s\n", parser->tmp);
	if (ft_islimiter(str[*off]) == TRUE)
		(*off)++;
	while (str[i])
	{
		quote_start(&squote.open, str[i], &squote.type);
		if (ft_islimiter(str[i]) == TRUE && squote.open == FALSE)
			break ;
		parser->tmp = join_char(parser->tmp, str[i]);
		i++;
	}
	parser->tmp = expand_name(parser->tmp, data, squote, off);
	printf("parser->tmp: %s\n", parser->tmp);
	return (TRUE);
}

t_bool	get_inout(int *off, char *str, t_parser *parser, t_data *data)
{
	int			i;
	t_quote		squote;

	i = 0;
	squote = (t_quote){FALSE, 0};
	while (ft_islimiter(str[*off]) == TRUE)
		(*off)++;
	*off += skip_spaces2(str + *off);
	i = *off;
	while (str[i])
	{
		quote_start(&squote.open, str[i], &squote.type);
		if ((ft_isspace(str[i]) == TRUE || ft_islimiter(str[i]) == TRUE)
			&& squote.open == FALSE)
			break ;
		parser->tmp = join_char(parser->tmp, str[i]);
		i++;
	}
	*off = i;
	parser->tmp = expand_name(parser->tmp, data, squote, off);
	if ((ft_islimiter(str[i]) == FALSE && str[i]) || str[i] == '\0')
		return (FALSE);
	return (TRUE);
}

char	*ft_reparsing(char *str, int i, t_data *data)
{
	t_quote	squote;
	char	*file;
	char	*args;
	char	*dst;
	int		j;

	file = ft_substr(str, 0, i);
	squote = (t_quote){FALSE, 0};
	dst = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!dst)
		return (free(str), ft_inputclear(&data->input), NULL);
	j = i;
	while (str[j])
	{
		quote_start(&squote.open, str[j], &squote.type);
		if (ft_islimiter(str[j]) == TRUE && squote.open == FALSE)
			break ;
		j++;
	}
	args = ft_substr(str, i, j);
	dst = ft_strjoin_2free(args, file);
	dst = ft_newstrjoin(dst, str + j);
	printf("dst: %s\n", dst);
	return (free(str), ft_inputclear(&data->input), dst);
}
//echo ciao > "file1 |" pippo 'amico|' ls
/*
squote = (t_quote){FALSE, 0};
	dst = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!dst)
		return (free(str), ft_inputclear(&data->input), NULL);
	k = i;
	j = -1;
	while (k > 0 && (ft_islimiter(str[k]) == FALSE || squote.open == TRUE))
		quote_start(&squote.open, str[k--], &squote.type);
	if (ft_islimiter(str[k - 1]) == TRUE)
		k--;
	while (str[++j] && j < k)
		dst[j] = str[j];
	tmp = ft_strncpy(str, k, i);
	while (str[i] && (ft_islimiter(str[i]) == FALSE || squote.open == TRUE))
	{
		quote_start(&squote.open, str[i], &squote.type);
		dst[j++] = str[i++];
	}
	k = 0;
	while (tmp && tmp[k])
		dst[j++] = tmp[k++];
	while (str[i])
		dst[j++] = str[i++];
	return (free(tmp), free(str), ft_inputclear(&data->input), dst);*/