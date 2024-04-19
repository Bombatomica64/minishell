/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/18 10:31:02 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	len_src;
	char	*new_string;

	i = 0;
	len_src = ft_strlen(s);
	if (start + len > len_src && start < len_src)
		len = len_src - start;
	else if (start >= len_src)
		len = 0;
	new_string = (char *)malloc((len + 1) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	while (i < len)
	{
		new_string[i] = s[i + start];
		i++;
	}
	new_string[len] = '\0';
	return (new_string);
}
/*#include <stdio.h>

int main() {
    const char *source = "This is a test string";
    unsigned int start = 5;
    size_t length = 9;

    char *substring = ft_substr(source, start, length);
    
    if (substring != NULL) {
        printf("Substring: %s\n", substring);
        free(substring); // Don't forget to free the memory when you're done
    } else {
        printf("Substring is NULL (invalid parameters)\n");
    }

    return 0;
}*/
