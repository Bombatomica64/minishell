/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:12:50 by lmicheli          #+#    #+#             */
/*   Updated: 2023/10/26 15:57:40 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s2;
	unsigned char	*s1;

	s1 = (unsigned char *)src;
	s2 = (unsigned char *)dest;
	if (!src && !dest)
		return (0);
	if (dest > src)
		while (n--)
			s2[n] = s1[n];
	else
		while (n--)
			*(s2++) = *(s1++);
	return (dest);
}
