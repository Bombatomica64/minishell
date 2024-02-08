/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:26:58 by lmicheli          #+#    #+#             */
/*   Updated: 2023/12/07 12:57:08 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
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
