/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/18 10:31:02 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strncpy_noquote(char *str, int start, int end)
// {
// 	char	*dst;
// 	int		i;

// 	if (!str)
// 		return (NULL);
// 	dst = (char *)malloc(sizeof(char) * (end - start + 1));
// 	if (!dst)
// 		return (NULL);
// 	i = 0;
// 	while (start < end)
// 	{
// 		if (str[start] == '\'' || str[start] == '\"')
// 			start++;
// 		dst[i] = str[start];
// 		i++;
// 		start++;
// 	}
// 	dst[i] = '\0';
// 	return (dst);
// }

char	*ft_strjoin_2free(char *old_str, char *buf)
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
	free(buf);
	return (res);
}

char	*ft_strjoin_2(char *old_str, char *buf)
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
	free(buf);
	return (res);
}

char	*ft_strndup(char *str, int i)
{
	char	*dst;
	int		j;

	dst = (char *)malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	j = 0;
	while (j < i)
	{
		dst[j] = str[j];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

int	ft_strlen_noquote(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (ft_isquote(str[i]) == TRUE)
			i++;
		count++;
		i++;
	}
	return (count);
}
