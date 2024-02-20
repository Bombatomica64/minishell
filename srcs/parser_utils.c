/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:12:34 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/20 17:44:01 by sgarigli         ###   ########.fr       */
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
			(*str)++;
			return (HEREDOC);
		}
		else
			return (INPUT);
	}
	else if (**str == '>')
	{
		(*str)++;
		if (**str == '>')
		{
			(*str)++;
			return (APPEND);
		}
		else
			return (TRUNC);
	}
	return (COMMAND);
}

char	*join_char(char *str, char c)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!str)
	{
		tmp = malloc(sizeof(char) * 2);
		if (!tmp)
			return (NULL);
		tmp[0] = c;
		tmp[1] = '\0';
		return (tmp);
	}
	tmp = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = c;
	tmp[i + 1] = '\0';
	free(str);
	return (tmp);
}
