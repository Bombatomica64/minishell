/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:11:17 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/28 16:07:34 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_name(char *str, int tmp_type, t_bool *quote, char **envp) 
{
	int		i ;
	char	quote_type;
	char	*tmp;

	i = 0;
	(void)envp;
	tmp = NULL;
	quote_type = '\0';
	skip_spaces(&str);
	while (str[i] != 0)
	{
		if (ft_isquote(str[i]))
		{
			quote_start(quote, str[i], &quote_type);
			if (tmp_type == BUILT_IN || tmp_type == COMMAND || (*quote == TRUE && str[i] != quote_type))
				tmp = join_char(tmp, str[i]);
			i++;
		}
		else
		{
			tmp = join_char(tmp, str[i]);
			i++;
		}
		if (ft_islimiter(str[i]) == TRUE && *quote == FALSE)
			break ;
	}
	// if (quote_error(tmp, quote) == TRUE)
	// 	return (NULL);
	expand_variables(&tmp, envp, quote, quote_type);
	return (tmp);
}

char	*get_path(char **tmp, t_type tmp_type, t_data *data)
{
	char	*tmp_path;
	int		i;
	int		j;

	tmp_path = NULL;
	i = 0;
	if (tmp_type == COMMAND || tmp_type == BUILT_IN)
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
		else if (tmp_type != BUILT_IN)
			*tmp = ft_strrchr(tmp_path, '/') + 1;
	}
	else if (tmp_type != HEREDOC)
	{
		printf("we tmp: %s\n", *tmp);
		tmp_path = refactor_path(*tmp, data, 0);
	}
	return (tmp_path);
}

t_bool	parser(char *str, t_data *data)
{
	int			i;
	t_parser	parser;
	t_bool		quote;

	quote = FALSE;
	i = count_limiter(str);
	if (i == ERROR)
		return (FALSE);
	while (i > 0)
	{
		skip_spaces(&str);
		parser.tmp_type = ft_file_type(&str);
		parser.tmp = get_name(str, parser.tmp_type, &quote, data->envp);
		parser.tmp = ft_freestrtrim(parser.tmp, " ");
		if (ft_isbuiltin(parser.tmp) == TRUE)
			parser.tmp_type = BUILT_IN;
		parser.tmp_path = get_path(&parser.tmp, parser.tmp_type, data);
		ft_inputadd_back(&(*data).input, ft_inputnew(parser.tmp, parser.tmp_path, parser.tmp_type));
		if (str != NULL && parser.tmp != NULL)
			str = ft_freesubstr(str, ft_strlen(parser.tmp) + 1, ft_strlen(str) - ft_strlen(parser.tmp));
		i--;
		free(parser.tmp);
		free(parser.tmp_path);
	}
	print_list((*data).input);
	free(str);
	return (TRUE);
}
// Path: srcs/parser.c
//ptr[32, | , 3 ,4]