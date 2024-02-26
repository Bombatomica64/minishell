/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:10:53 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/26 18:37:30 by lmicheli         ###   ########.fr       */
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

int	free_return(t_data *data, int status)
{
	ft_inputclear(&data->input);
	free_matrix(&data->pipex.cmd);
	free(data->pipex.path);
	free(data->pipex.filein);
	free(data->pipex.fileout);
	// free(data->pipex.connector);
	return (status);
}

void	free_close(t_data *data, int status)
{
	free_return(data, status);
	free_matrix(&data->envp);
	free(data->home);
	rl_clear_history();
	exit (status);
}
