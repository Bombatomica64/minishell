/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:21:56 by lmicheli          #+#    #+#             */
/*   Updated: 2023/10/26 15:59:09 by lmicheli         ###   ########.fr       */
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

char	*ft_strtrim(char const *s1, char const *set)
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
/*
#include <stdio.h> 
int main() {
    char *s1 = "   Hello, World!   ";
    char *set = " ";
    char *trimmed = ft_strtrim(s1, set);

    if (trimmed) {
        printf(" Original String: \"%s\"\n", s1);
        printf("Trimmed String: \"%s\"\n", trimmed);
        free(trimmed); // Don't forget to free the memory allocated by ft_strtrim
    } else {
        printf("Allocation or input error occurred.\n");
    }

    return 0;
}
*/