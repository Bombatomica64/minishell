/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:04:41 by sgarigli          #+#    #+#             */
/*   Updated: 2024/03/12 12:17:30 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*free_strrchr(char *str, char c, int **offset)
{
	int		i;
	int		len;
	char	*tmp;

	tmp = NULL;
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == c)
		{
			**offset = i;
			break ;
		}
		i--;
	}
	len = ft_strlen(str);
	while (i < len)
	{
		tmp = join_char(tmp, str[i]);
		i++;
	}
	free(str);
	return (tmp);
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

char	*cut_string(int len, char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!ft_strlen(str) || len >= (int)ft_strlen(str))
		return (free(str), NULL);
	tmp = malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	if (!tmp)
		return (NULL);
	while (str[len])
	{
		tmp[i] = str[len];
		i++;
		len++;
	}
	tmp[i] = '\0';
	free(str);
	return (tmp);
}
