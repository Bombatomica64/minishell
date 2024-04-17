/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:47:02 by gduranti          #+#    #+#             */
/*   Updated: 2024/04/15 11:55:57 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*un_s;
	unsigned char	un_c;
	size_t			i;

	un_s = (unsigned char *)s;
	un_c = (unsigned char)c;
	i = 0;
	if (!s && n == 0)
		return (NULL);
	while (i < n)
	{
		if (un_s[i] == un_c)
			return ((void *)&un_s[i]);
		i++;
	}
	return (NULL);
}
/*int main ()
{
	printf("%s",((char *)ft_memchr("qwertyuiopasdf",'p',10)));
}*/