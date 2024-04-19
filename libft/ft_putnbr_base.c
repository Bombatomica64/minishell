/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/18 10:31:02 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	checksize(unsigned int temp, int size)
{
	while (temp > 0)
	{
		size++;
		temp /= 16;
	}
	return (size);
}

int	ft_putnbr_base(unsigned int nbr, char *base)
{
	int				i;
	char			*number;
	int				size;
	unsigned int	temp;

	size = 0;
	temp = nbr;
	size = checksize(temp, size);
	number = (char *)malloc(size * sizeof(char));
	if (!number)
		return (-1);
	i = size - 1;
	while (nbr > 0 || i > -1)
	{
		temp = nbr % 16;
		number[i] = (char)base[temp];
		nbr /= 16;
		i--;
	}
	number[size] = '\0';
	i = ft_putstr_nofree(number);
	free (number);
	return (i);
}

static int	checksize_long(unsigned long int temp, int size)
{
	if (temp == 0)
		return (1);
	while (temp > 0)
	{
		size++;
		temp /= 16;
	}
	return (size);
}

int	ft_putnbr_base_long(unsigned long nbr, char *base)
{
	int					i;
	char				*number;
	int					size;
	unsigned long int	temp;

	size = 0;
	temp = nbr;
	size = checksize_long(temp, size);
	number = (char *)malloc((size + 1) * sizeof(char));
	if (!number)
		return (0);
	if (nbr == 0)
		number[0] = '0';
	i = size - 1;
	while (nbr > 0)
	{
		temp = nbr % 16;
		number[i] = (char)base[temp];
		nbr /= 16;
		i--;
	}
	number[size] = '\0';
	i = ft_putstr(number);
	return (i);
}

int	ft_put_pointer(unsigned long int poi)
{
	int		i;

	i = 0;
	if (poi == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write (1, "0x", 2);
	i += 2;
	i += ft_putnbr_base_long(poi, "0123456789abcdef");
	return (i);
}
