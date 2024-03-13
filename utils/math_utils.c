/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:08:59 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/13 15:40:12 by gduranti         ###   ########.fr       */
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

t_bool	ft_atoibool(char *str, int *nbr)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (FALSE);
		res = res * 10 + str[i] - '0';
		i++;
	}
	res *= sign;
	if (res > INT_MAX || res < INT_MIN)
		return (FALSE);
	*nbr = (int)res;
	return (TRUE);
}
