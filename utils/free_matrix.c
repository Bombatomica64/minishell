/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:10:53 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/19 16:23:17 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	ft_freenclose(t_data *data)
{
	int i;

	i = -1;
	ft_inputclear(&data->input);
	free_matrix(data->in_p.cmds);
	free_matrix(data->in_p.files);
	free(data->input);
}
