/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:20:51 by lmicheli          #+#    #+#             */
/*   Updated: 2023/10/28 12:52:57 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t				i;
	unsigned char		*p;

	i = 0;
	p = s;
	while (i < n)
	{
		*p++ = '\0';
		i++;
	}
}
/*#include <stdio.h>
int main ()
{
	char s[] = "qweuollao";
	ft_bzero(s, 2);
	printf("%s \n",&s[4]);
}*/