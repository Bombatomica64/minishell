/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/18 10:31:02 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_to_put(char c, va_list lst)
{
	int		add;

	add = 0;
	if (c == 'i' || c == 'd')
		add += ft_putstr(ft_itoa(va_arg(lst, int)));
	else if (c == 'c')
		add += ft_putchar((unsigned char)va_arg(lst, int));
	else if (c == 's')
		add += ft_putstr_nofree(va_arg(lst, char *));
	else if (c == 'p')
		add += ft_put_pointer(va_arg(lst, unsigned long int));
	else if (c == 'u')
		add += ft_putstr(ft_unsigned_itoa(va_arg(lst, unsigned long int)));
	else if (c == 'x')
		add += ft_putnbr_base_long(va_arg(lst, unsigned int),
				"0123456789abcdef");
	else if (c == 'X')
		add += ft_putnbr_base_long(va_arg(lst, unsigned int),
				"0123456789ABCDEF");
	else if (c == '%')
		add += ft_putchar('%');
	return (add);
}

int	ft_printf(const char *format, ...)
{
	va_list		lst;
	int			i;
	int			nbr_chr;

	va_start (lst, format);
	i = 0;
	nbr_chr = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			nbr_chr += check_to_put(format[i + 1], lst);
			i++;
		}
		else
		{
			nbr_chr++;
			write(1, &format[i], 1);
		}
		i++;
	}
	va_end(lst);
	return (nbr_chr);
}
/*
int	main(void)
{
// Test di base
	ft_printf("Hello, world!\n");
	ft_printf("%d\n", 1234);
	ft_printf("%s\n", NULL);
	ft_printf("%d\n", 1234);
	ft_printf("%s\n", "Ciao, mondo!");
	int* pointer = NULL;
	ft_printf("%p\n", pointer);
	ft_printf("%s\n", pointer);
	ft_printf("%d\n", -1234567890123456789);
//	printf("Norm:%d\n", -1234567890123456789);
	ft_printf("%s\n", "Stringa troppo lunga");
} */
/* *char	str[] = "Hello, World!";
	int		num;
	int		*p;

	num = -42;
	p = &num; */
