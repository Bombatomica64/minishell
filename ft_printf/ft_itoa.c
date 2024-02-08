/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:37:21 by lmicheli          #+#    #+#             */
/*   Updated: 2023/10/26 15:55:18 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*make_number(int num_len, long b)
{
	long	i;
	char	*array;
	char	c;

	i = 0;
	array = (char *)ft_calloc(sizeof(char), (num_len + 1));
	if (array == NULL)
		return (NULL);
	if (b < 0)
	{
		array[0] = '-';
		b = -b;
	}
	if (b == 0)
		array[0] = '0';
	while (b > 0)
	{
		c = (b % 10) + '0';
		array[num_len - i - 1] = c;
		b = b / 10;
		i++;
	}
	array[num_len] = '\0';
	return (array);
}

static int	ft_check_len(long n)
{
	long		i;
	size_t		num;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		num = n;
		i++;
	}
	else
		num = n;
	while (num >= 10)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		num_len;
	long	a;
	char	*number;

	a = n;
	num_len = ft_check_len(a);
	number = make_number(num_len, a);
	return (number);
}

/*
int main() {
    int test_cases[] = {0, -12345, 6789, INT_MIN, INT_MAX};
    
    for (long unsigned int i = 0; i < sizeof(test_cases) /
	 sizeof(test_cases[0]); i++) {
        int n = test_cases[i];
        char *result = ft_itoa(n);
        if (result == NULL) {
            printf("Memory allocation error\n");
            return 1;  // Exit with an error code
        }
        printf("Integer: %d, String: %s\n", n, result);
     
    }
    
    return 0;  // Exit with a success code
}*/