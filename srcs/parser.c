/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:50:51 by mruggier          #+#    #+#             */
/*   Updated: 2024/02/22 11:58:59 by sgarigli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char *str, int tmp_type)
{
	int		i;
	t_bool	quote;
	char	quote_type;
	char	*tmp;

	i = 0;
	tmp = NULL;
	quote = FALSE;
	quote_type = '\0';
	skip_spaces(&str);// da fare con tutti gli spazi
	while (is_not_limiter(str[i]))
	{
		if ((str[i] == '\'' || str[i] == '\"'))
		{
			//printf("tmpprima = %s\n", tmp);
			quote_start(&quote, str[i], &quote_type);
			if (tmp_type == BUILT_IN || tmp_type == COMMAND)
				tmp = join_char(tmp, str[i]);
			else if (quote == TRUE && str[i] != quote_type)
				tmp = join_char(tmp, str[i]);
		}
		else
			tmp = join_char(tmp, str[i]);
		i++;
	}
	if (quote == TRUE)
	{
		quote_waiting(&tmp, &quote, &quote_type, tmp_type);
		if (!(tmp_type == BUILT_IN || tmp_type == COMMAND))
			tmp = ft_freesubstr(tmp, 0, ft_strlen(tmp) - 1);
	}
	return (tmp);
}

char	*get_path(char **tmp, t_type tmp_type, t_data *data)
{
	char	*tmp_path;
	int		i;
	int		j;

	i = 0;
	if (tmp_type == COMMAND || tmp_type == BUILT_IN)
	{
		while ((*tmp)[i] != ' ' && (*tmp)[i] != '\0')
		{
			if ((*tmp)[i] == '\'' || (*tmp)[i] == '\"')
			{
				i++;
				j = i;
				while ((*tmp)[j] != '\'' && (*tmp)[j] != '\"')
					j++;
				tmp_path = ft_strjoin_2free(tmp_path, ft_strncpy_noquote(*tmp, i, j));
				i = j;
			}
			else
				tmp_path = join_char(tmp_path, (*tmp)[i]);
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

void	parser(char *str, t_data *data)
{
	char	*tmp;
	char	*tmp_path;
	t_type	tmp_type;

	skip_spaces(&str);
	tmp_type = ft_file_type(&str);
	tmp = get_name(str, tmp_type);
	//tmp_path = get_path(&tmp, tmp_type, data);
	printf("str = %s\n", str);
	printf("tmp = %s\n", tmp);
	printf("type = %d\n", tmp_type);
	//printf("path = %s\n", tmp_path);
	exit(EXIT_FAILURE);
	// ft_inputadd_back(&(*data).input, ft_inputnew(tmp, tmp_path, tmp_type));
	(void)data;
	(void)tmp;
	(void)tmp_path;
	(void)tmp_type;
}
// Path: srcs/parser.c