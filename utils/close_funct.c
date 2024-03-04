/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:10:53 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/04 12:17:12 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_matrix(char ***mtx)
{
	size_t	i;

	if (!mtx || !*mtx)
		return ;
	i = 0;
	while ((*mtx)[i])
	{
		free((*mtx)[i]);
		i++;
	}
	free(*mtx);
	*mtx = NULL;
}

void	free_array_matrix(int **matrix, int size)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (i < size)
	{
		// close(matrix[i][0]);
		// close(matrix[i][1]);
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	free_return(t_data **data, int status)
{
	ft_inputclear(&(*data)->input);
	free_array_matrix((*data)->fd, (*data)->pipe_nbr);
	return (status);
}

void	free_close(t_data **data, int status)
{
	free_return(data, status);
	free_matrix(&(*data)->envp);
	free((*data)->home);
	if ((*data)->pwd)
		free((*data)->pwd);
	exit (status);
}
