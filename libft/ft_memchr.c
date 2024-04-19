/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/18 10:31:02 by lmicheli         ###   ########.fr       */
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
