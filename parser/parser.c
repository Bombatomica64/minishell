/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:11:17 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/28 10:29:56 by lmicheli         ###   ########.fr       */
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
	if (quote_error(tmp, quote) == TRUE)
		return (NULL);
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
				ft_error("path_execve in get_path", NO_PATH, 127, data);
		}
		else if (tmp_type != BUILT_IN)
			*tmp = ft_strrchr(tmp_path, '/') + 1;
	}
	else if (tmp_type != HEREDOC)
	{
		tmp_path = refactor_path(*tmp, data, 0);
		printf("tmp_path: %s\n", tmp_path);
	}
	return (tmp_path);
}

t_bool	parser(char *str, t_data *data)
{
	int		i;
	char	*tmp;
	char	*tmp_path;
	t_type	tmp_type;
	t_bool	quote;

	quote = FALSE;
	i = count_limiter(str);
	if (i == ERROR)
		return (FALSE);
	while (i > 0)
	{
		skip_spaces(&str);
		tmp_type = ft_file_type(&str);
		tmp = get_name(str, tmp_type, &quote, data->envp);
		printf("tmp: %s\n", tmp);
		if (ft_isbuiltin(tmp) == TRUE)
			tmp_type = BUILT_IN;
		tmp_path = get_path(&tmp, tmp_type, data);
		//tmp_path = NULL;
		ft_inputadd_back(&(*data).input, ft_inputnew(tmp, tmp_path, tmp_type));
		printf("str: %s\n", str);
		str = ft_freesubstr(str, ft_strlen(tmp) + 1, ft_strlen(str) - ft_strlen(tmp));
		i--;
	}
	print_list((*data).input);
	return (TRUE);
}
// Path: srcs/parser.c