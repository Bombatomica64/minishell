/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/18 10:31:02 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*check_null(char const *s1)
{
	char	*new_string;

	if (*s1 == '\0')
	{
		new_string = (char *)malloc(1 * sizeof(char));
		if (new_string == NULL)
			return (NULL);
		new_string[0] = '\0';
		return (new_string);
	}
	return (NULL);
}

static char	*all_to_trim(int start, int len, const char *s1)
{
	char	*new_string;

	if (start == len || check_null(s1) != NULL)
	{
		new_string = (char *)malloc(1 * sizeof(char));
		if (new_string == NULL)
			return (NULL);
		new_string[0] = '\0';
		return (new_string);
	}
	return (NULL);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		start;
	int		end;
	int		len;
	char	*new_string;

	if (*s1 == '\0')
		return (ft_strdup(""));
	len = ft_strlen(s1);
	start = 0;
	while (start < len && ft_strchr(set, s1[start]) != NULL)
		start++;
	if (all_to_trim(start, len, s1) != NULL)
	{
		new_string = all_to_trim(start, len, s1);
		return (new_string);
	}
	end = 0;
	while (end < len && ft_strchr(set, s1[len - end - 1]) != NULL)
		end++;
	new_string = (char *)malloc((len - start - end + 1) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	new_string[0] = '\0';
	ft_strlcat(new_string, s1 + start, (len - start - end + 1));
	return (new_string);
}

char	*ft_freestrtrim(char *s1, char *set)
{
	int		start;
	int		end;
	int		len;
	char	*new_string;

	if (*s1 == '\0')
		return (ft_strdup(""));
	len = ft_strlen(s1);
	start = 0;
	while (start < len && ft_strchr(set, s1[start]) != NULL)
		start++;
	if (all_to_trim(start, len, s1) != NULL)
	{
		new_string = all_to_trim(start, len, s1);
		return (new_string);
	}
	end = 0;
	while (end < len && ft_strchr(set, s1[len - end - 1]) != NULL)
		end++;
	new_string = (char *)malloc((len - start - end + 1) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	new_string[0] = '\0';
	ft_strlcat(new_string, s1 + start, (len - start - end + 1));
	return (free(s1), new_string);
}
