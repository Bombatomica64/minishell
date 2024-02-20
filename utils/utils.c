/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:10:41 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/20 12:11:45 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strncpy_noquote(char *str, int start, int end)
{
	char	*dst;
	int		i;

	if (!str)
		return (NULL);
	dst = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (start < end)
	{
		if (str[start] == '\'' || str[start] == '\"')
			start++;
		dst[i] = str[start];
		i++;
		start++;
	}
	dst[i] = '\0';
	return (dst);
}

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

char	**matrix_dup(char **matrix)
{
	char	**new_matrix;
	int		i;

	if (!matrix)
		return (NULL);
	i = 0;
	while (matrix[i] != NULL)
		i++;
	new_matrix = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_matrix)
		return (NULL);
	i = 0;
	while (matrix[i] != NULL)
	{
		new_matrix[i] = ft_strdup(matrix[i]);
		i++;
	}
	new_matrix[i] = NULL;
	return (new_matrix);
}

t_bool	is_not_limiter(char c)
{
	if (c != '<' && c != '>' && c != '\0' && c != '|')
		return (TRUE);
	return (FALSE);
}

void	skip_spaces(char **str)
{
	while (**str == ' ' && **str != '\0')
		(*str)++;
}
