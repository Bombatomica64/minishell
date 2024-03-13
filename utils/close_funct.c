/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:10:53 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/13 12:10:24 by lmicheli         ###   ########.fr       */
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
	if (size == 0)
		return ;
	while (i < size)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	free_return(t_data **data, int status)
{
	ft_inputclear(&(*data)->input);
	close(0);
	close(1);
	printf("session closed\n");
	free_array_matrix((*data)->fd, (*data)->pipe_nbr);
	return (status);
}

void	free_close(t_data **data, int status)
{
	free_return(data, status);
	close((*data)->original_stdin);
	close((*data)->original_stdout);
	close(0);
	close(1);
	free_matrix(&(*data)->envp);
	free((*data)->home);
	if ((*data)->pwd)
		free((*data)->pwd);
	exit (status);
}
