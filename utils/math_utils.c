/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:08:59 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/13 10:44:34 by lmicheli         ###   ########.fr       */
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
