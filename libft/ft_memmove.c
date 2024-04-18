/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/18 10:31:02 by lmicheli         ###   ########.fr       */
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
