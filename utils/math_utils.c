/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:08:59 by lmicheli          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/28 17:46:18 by mruggier         ###   ########.fr       */
=======
/*   Updated: 2024/03/29 11:05:52 by lmicheli         ###   ########.fr       */
>>>>>>> 3cf1ceba698aadd485a7bd9ac54794bd941b6f7d
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
	
	/*if (str[i] == '0')  TODO: perche' mandi FALSE se il numero e' da 0 a 9? exit 1 deve chiudere con 1
		return (TRUE);*/
	if (strcmp(str, "-9223372036854775808") == 0)
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
