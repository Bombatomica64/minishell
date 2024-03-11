/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:45:24 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/11 12:51:46 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_isinset(char c, char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_result(char *s1, size_t start, size_t end)
{
	char	*dst;
	size_t	i;

	i = 0;
	if (!s1[start])
	{
		dst = (char *)malloc(sizeof(char));
		if (dst == NULL)
			return (NULL);
		dst[0] = '\0';
		return (dst);
	}
	dst = (char *)malloc((end - start + 2) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	while (start <= end)
	{
		dst[i] = s1[start];
		start++;
		i++;
	}
	dst[i] = '\0';
	free(s1);
	return (dst);
}

char	*ft_strtrimfree(char *s1, char *set)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_result(s1, 0, 0));
	while (s1[start] && ft_isinset(s1[start], set) == 1)
		start++;
	while (s1[end])
		end++;
	if (start == end)
		return (ft_result(s1, start, end));
	end--;
	while (ft_isinset(s1[end], set) == 1)
		end--;
	return (ft_result(s1, start, end));
}

int	find_first(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*strjoin_n_free1(char *line, char *buff, int index)
{
	int		i;
	int		new_str_len;
	char	*new_str;

	i = 0;
	new_str_len = ft_strlen(line) + index;
	new_str = malloc(ft_strlen(line) + index + 1);
	if (new_str)
	{
		while (line[i])
		{
			new_str[i] = line[i];
			i++;
		}
		while (i < new_str_len)
		{
			new_str[i] = buff[i - ft_strlen(line)];
			i++;
		}
		new_str[new_str_len] = '\0';
	}
	free(line);
	return (new_str);
}
