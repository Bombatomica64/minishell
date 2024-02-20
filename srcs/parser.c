/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:50:51 by mruggier          #+#    #+#             */
/*   Updated: 2024/02/20 12:11:39 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (COMMAND);
}

void	quote_start(t_bool *quote, char c, char quote_type)
{
	if (quote_type == '\0')
	{
		quote_type = c;
		*quote = TRUE;
		return ;
	}
	if (c == quote_type)
	{
		if (*quote == FALSE)
			*quote = TRUE;
		else
			*quote = FALSE;
		quote_type = '\0';
	}
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

char	*get_path(char **tmp, t_type tmp_type, t_data *data)
{
	char	*tmp_path;
	int		i;
	int		j;
	char	*comm;

	i = 0;
	if (tmp_type == COMMAND || tmp_type == BUILT_IN)
	{
		while ((*tmp)[i] != ' ' && (*tmp)[i] != '\0')
		{
			if ((*tmp)[i] == "\'" || (*tmp)[i] == '\"')
			{
				i++;
				j = i;
				while ((*tmp)[j] != "\'" || (*tmp)[j] != '\"')
					j++;
				ft_strjoin_2free(tmp_path, ft_strncpy_noquote(*tmp, i, j));
				i = j;
			}
			else
				ft_newstrjoin(tmp_path, (*tmp)[i]);
			i++;
		}
		if (ft_strrchr(tmp_path, '/') == NULL)
			tmp_path = path_execve(tmp_path, data->envp);
		else
			*tmp = ft_strrchr(tmp_path, '/') + 1;
	}
	else if (tmp_type != HEREDOC)
	{
		if (ft_strrchr(*tmp, '/') == NULL)
			tmp_path = ft_newstrjoin(data->directory, *tmp);
		else if (*tmp[0] == '/' || *tmp[0] == '~')
			tmp_path = ft_strdup(*tmp);
		else
			tmp_path = ft_newstrjoin(data->directory, *tmp);
	}
	return (tmp_path);
}

void	ft_parser(char *str, t_data *data)
{
	char	*tmp;
	char	*tmp_path;
	t_type	tmp_type;
	int		i;

	i = 0;
	skip_spaces(&str);
	tmp_type = ft_file_type(&str);
	tmp = get_name(&str, tmp_type);
	tmp_path = get_path(&tmp, tmp_type, data);
	ft_inputadd_back(&(*data).input, ft_inputnew(tmp, tmp_path, tmp_type));
}
// Path: srcs/parser.c