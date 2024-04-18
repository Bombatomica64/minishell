/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/18 10:31:02 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *str, int c)
{
	const char	*p;

	p = str;
	if (!str)
		return (NULL);
	if ((unsigned char)c == 0)
		return ((char *)&p[ft_strlen(str)]);
	while (*p != '\0')
	{
		if (*p == (unsigned char)c)
			return ((char *)p);
		p++;
	}
	return (NULL);
}
/*int main()
{
	const char	str[]= "vado al bar";
	int	c = 0;
	printf("%s",ft_strchr(str,c));
}*/
