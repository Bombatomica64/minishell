/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:11:17 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/27 16:41:19 by sgarigli         ###   ########.fr       */
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
		{
			printf("%s\n", get_env_value(data->envp, "PATH="));
			tmp_path = path_execve(tmp_path, data->envp);
			if (tmp_path == NULL)
				ft_error("path_execve in get_path", NO_PATH, 127, data);
		}
		else
			*tmp = ft_strrchr(tmp_path, '/') + 1;
	}
	else if (tmp_type != HEREDOC)
	{
		if (*tmp[0] == '/')
			tmp_path = ft_strdup(*tmp);
		else if (strncmp(*tmp, "./", 2) == 0)
			tmp_path = ft_strjoin(getcwd(NULL, 0), *tmp + 1);
		else if (strncmp(*tmp, "../", 3) == 0) //TODO: sbagliato, fare cd prima. 
		{
			tmp_path = ft_strjoin(tmp_path, *tmp + 2);
		}
		else if (strncmp(*tmp, "~/", 2) == 0) //TODO: se "~/c" non funziona perche' cancelliamo le virgolette
		{
			tmp_path = ft_strjoin(data->home, *tmp + 1);
		}
		else
		{
			tmp_path = ft_strjoin("/", *tmp);
			tmp_path = ft_strjoin(getcwd(NULL, 0), tmp_path);
		}
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
		if (quote == TRUE)
		{
			free(tmp);
			printf("quote error\n");
			return (FALSE);
		}
		tmp_path = get_path(&tmp, tmp_type, data);
		//tmp_path = NULL;
		ft_inputadd_back(&(*data).input, ft_inputnew(tmp, tmp_path, tmp_type));
		str = ft_freesubstr(str, ft_strlen(tmp) + 1, ft_strlen(str) - ft_strlen(tmp));
		i--;
	}
	print_list((*data).input);
	return (TRUE);
}
// Path: srcs/parser.c