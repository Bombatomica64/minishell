/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/29 12:35:44 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	print_intmatrix(int **matrix, int rows, int cols)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (i < rows)
	{
		j = 0;
		printf("row %d: ", i);
		while (j < cols)
		{
			printf("[%d] ", matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

t_bool	ft_atoibool(char *str, unsigned int *nbr, int i, int sign)
{
	long long	res;

	if (ft_strcmp(str, "-9223372036854775808") == 0)
	{
		*nbr = (unsigned int)LLONG_MIN;
		return (TRUE);
	}
	res = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9') || res > res * 10 + str[i] - '0')
			return (FALSE);
		res = res * 10 + str[i] - '0';
		i++;
	}
	res *= sign;
	*nbr = (unsigned int)res;
	return (TRUE);
}
