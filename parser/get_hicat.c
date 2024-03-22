/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hicat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:05:27 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/22 12:33:36 by sgarigli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	get_command(int *off, char *str, t_parser *prs, t_data *data)
{
	int		i;
	t_quote	squote;

	(void)data;
	i = 0;
	squote = (t_quote){FALSE, 0};
	i = skip_spaces2(str);
	if (ft_islimiter(str[i]) == TRUE)
	{
		(*off)++;
		i++;
	}
	while (str[i] && (ft_islimiter(str[i]) == FALSE || squote.open == TRUE))
	{
		quote_start(&squote.open, str[i], &squote.type);
		prs->tmp = join_char(prs->tmp, str[i]);
		i++;
	}
	//parser->tmp = expand_name(parser->tmp, data, squote, off);
	return (TRUE);
}

t_bool	get_inout(int *off, char *str, t_parser *prs, t_data *data)
{
	int			i;
	t_quote		squote;

	(void)data;
	squote = (t_quote){FALSE, 0};
	i = skip_spaces2(str);
	while (ft_islimiter(str[i]) == TRUE)
		(i)++;
	i += skip_spaces2(str + i);
	// i = *off;
	while (str[i])
	{
		quote_start(&squote.open, str[i], &squote.type);
		if ((ft_isspace(str[i]) == TRUE || ft_islimiter(str[i]) == TRUE)
			&& squote.open == FALSE)
			break ;
		prs->tmp = join_char(prs->tmp, str[i]);
		i++;
	}
	*off = i;
	*off += skip_spaces2(str + *off);
	if (str[*off] == '\0')
		return (TRUE);
	if (ft_islimiter(str[*off]) == FALSE)
		return (FALSE);
	return (TRUE);
}

char	*ft_reparsing(char *str, int i, t_data *data, t_quote squote)
{
	char	*tmp;
	char	*dst;
	int		j;
	int		k;

	dst = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!dst)
		return(free(str), ft_inputclear(&data->input), NULL);
	k = i;
	j = -1;
	while (k > 0 && (ft_islimiter(str[k]) == FALSE || squote.open == TRUE))
		quote_start(&squote.open, str[k--], &squote.type);
	if ( k > 0 && ft_islimiter(str[k - 1]) == TRUE)
		k--;
	while(str[++j] && j < k)
		dst[j] = str[j];
	tmp = ft_strncpy(str, k, i);
	while(str[i] && (ft_islimiter(str[i]) == FALSE || squote.open == TRUE))
	{
		quote_start(&squote.open, str[i], &squote.type);
		dst[j++] = str[i++];
	}
	dst = ft_strjoin_2free(ft_input2str(&data->input),
		ft_newstrjoin(ft_strjoin_2free(dst, tmp), &str[i]));
	dst = ft_strtrimfree(dst, " \t\r\n\v\f", &i);
	return (free(str), ft_inputclear(&data->input), dst);
}

// lasciamogliela, magari si arrabbia
// char	*ft_reparsing(char *str, int i, t_data *data)
// {
// 	t_quote	squote;
// 	char	*file;
// 	char	*args;
// 	char	*dst;
// 	int		j;

// 	file = ft_substr(str, 0, i);
// 	squote = (t_quote){FALSE, 0};
// 	dst = ft_calloc(ft_strlen(str) + 1, sizeof(char));
// 	if (!dst)
// 		return (free(str), ft_inputclear(&data->input), NULL);
// 	j = i;
// 	while (str[j])
// 	{
// 		quote_start(&squote.open, str[j], &squote.type);
// 		if (ft_islimiter(str[j]) == TRUE && squote.open == FALSE)
// 			break ;
// 		j++;
// 	}
// 	args = ft_substr(str, i, j);
// 	dst = ft_strjoin_2free(args, file);
// 	dst = ft_newstrjoin(dst, str + j);
// 	dst = ft_strjoin_2free(ft_input2str(&data->input), dst);
// 	return (free(str), ft_inputclear(&data->input), dst);
// }
