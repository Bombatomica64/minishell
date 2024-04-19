/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/18 10:31:02 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>

char	*ft_newstrjoin(char *old_str, char *buf)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!old_str)
	{
		old_str = (char *)malloc(1 * sizeof(char));
		if (!old_str || !buf)
			return (NULL);
		old_str[0] = '\0';
	}
	res = malloc(sizeof(char) * (ft_strlen(old_str) + ft_strlen(buf) + 1));
	if (!res)
		return (0);
	i = -1;
	j = 0;
	if (old_str)
		while (old_str[++i] != '\0')
			res[i] = old_str[i];
	while (buf[j] != '\0')
		res[i++] = buf[j++];
	res[ft_strlen(old_str) + ft_strlen(buf)] = '\0';
	free(old_str);
	return (res);
}

char	*ft_correctline(char *old_str)
{
	char	*line;
	int		i;

	i = 0;
	if (!old_str[i])
		return (NULL);
	while (old_str[i] && old_str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (0);
	i = 0;
	while (old_str[i] && old_str[i] != '\n')
	{
		line[i] = old_str[i];
		i++;
	}
	if (old_str[i] == '\n')
	{
		line[i] = old_str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_resto(char *old_str)
{
	int		i;
	int		j;
	char	*returnline;

	i = 0;
	while (old_str[i] && old_str[i] != '\n')
		i++;
	if (!old_str[i])
	{
		free(old_str);
		return (NULL);
	}
	returnline = malloc(sizeof(char) * (ft_strlen(old_str) - i + 1));
	if (!returnline)
		return (0);
	i++;
	j = 0;
	while (old_str[i])
		returnline[j++] = old_str[i++];
	returnline[j] = '\0';
	free(old_str);
	return (returnline);
}
