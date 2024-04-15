/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:10:27 by gduranti          #+#    #+#             */
/*   Updated: 2024/04/15 11:55:57 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	stamp(char nb, int fd)
{
	write (fd, &nb, 1);
}

static void	ft_putnbr(int nb, int fd)
{
	long	a;
	long	b;

	a = nb;
	if (a < 0)
	{
		a = a * -1;
		write(fd, "-", 1);
	}
	if (a >= 10)
	{
		b = a / 10;
		ft_putnbr(b, fd);
		ft_putnbr(a % 10, fd);
	}
	else
	{
		stamp(a + '0', fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	ft_putnbr(n, fd);
}
