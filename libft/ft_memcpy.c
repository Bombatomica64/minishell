/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/18 10:31:02 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest_char;
	unsigned char	*src_char;

	i = 0;
	if (!dest && !src)
		return (NULL);
	dest_char = (unsigned char *)dest;
	src_char = (unsigned char *)src;
	while (i < n)
	{
		dest_char[i] = src_char[i];
		i++;
	}
	return (dest);
}
/*#include <stdio.h>
#include <stdlib.h>  // for memory allocation functions

int main()
{
    char src[] = "mare1223";  // Source data
    char dest[10];         // Destination buffer with enough space
    ft_memcpy(dest, src, 5);
    printf("%s", dest);
    return 0;
}*/
