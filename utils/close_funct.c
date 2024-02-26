/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:10:53 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/26 10:44:45 by lmicheli         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

void	pass_envp(char **envp, int fd)
{
	size_t	i;

	i = 0;
	dup2(fd, STDOUT_FILENO);
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
}

void	freenclose(t_data *data)
{
	ft_inputclear(&data->input);
	pass_envp(data->envp, data->fd[1]);
	free(data->input);
}
