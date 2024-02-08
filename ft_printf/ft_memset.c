/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:55:44 by lmicheli          #+#    #+#             */
/*   Updated: 2023/10/26 15:57:44 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		*p++ = (unsigned char)c;
		i++;
	}
	return (s);
}
/*#include <stdio.h>
int main() {
    char buffer[20];
    int i;

    // Inizializza l'array con zeri
    for (i = 0; i < 20; i++) {
        buffer[i] = 0;
    }

    // Stampa il contenuto dell'array prima di utilizzare ft_memset
    printf("Array prima di ft_memset:\n");
    for (i = 0; i < 20; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    ft_memset(buffer, 42, 10);

    // Stampa il contenuto dell'array dopo l'utilizzo di ft_memset
    printf("Array dopo ft_memset:\n");
    for (i = 0; i < 20; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    return 0;
}
*/