/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/18 10:31:02 by lmicheli         ###   ########.fr       */
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
