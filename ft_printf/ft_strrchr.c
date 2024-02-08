/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:05:53 by lmicheli          #+#    #+#             */
/*   Updated: 2023/10/26 15:59:05 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	unsigned char	*p;
	int				i;
	int				last_pos;

	p = (unsigned char *)str;
	i = 0;
	last_pos = -1;
	if ((unsigned char)c == 0)
	{
		p = (unsigned char *)str + ft_strlen(str);
		return ((char *)p);
	}
	while (*p)
	{
		if (*p == (unsigned char)c)
			last_pos = i;
		p++;
		i++;
	}
	if (last_pos >= 0)
		return ((char *)str + last_pos);
	return (NULL);
}
/*int main()
{
	const char	str[]= "vado al barrett vez";
	int	c = 111;
	printf("%s",ft_strrchr(str,c));
}*/
