/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:10:53 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/23 18:43:40 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_matrix(char ***mtx)
{
	size_t	i;

	i = 0;
	if (!mtx)
		return ;
	while ((*mtx)[i])
	{
		free((*mtx)[i]);
		i++;
	}
	free(*mtx);
	mtx = NULL;
}

void	freenclose(t_data *data)
{
	ft_inputclear(&data->input);
	free_matrix(&data->in_p.cmds);
	free_matrix(&data->in_p.files);
	//print_matrix + dup2(fd[0], STDOUT_FILENO);
	free(data->input);
}
