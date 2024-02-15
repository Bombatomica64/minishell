/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_inout.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:05:07 by marvin            #+#    #+#             */
/*   Updated: 2024/02/13 16:05:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fd_in(t_data data)
{
	//printf("daaaaaaaaata.nb_total = %d\n", data.nb_total);
	while (data.nb_total > 0)
	{
		data.nb_total--;
		printf("data.input[%d].file.type = %d\n", data.nb_total, data.input[data.nb_total].file.type);
		if (data.input[data.nb_total].file.type == INPUT || data.input[data.nb_total].file.type == HEREDOC)
			return (data.input[data.nb_total].file.fd);
	}
	return (STDIN_FILENO);
}

void	ft_fd_out(t_data *data) //mette nell'array solo gli fd out consecutivi
{
	int	i;
	int	fdouts;

	i = 0;
	fdouts = 0;
	while (i < data->nb_total && (data->input[i].file.type != TRUNC && data->input[i].file.type != APPEND))
		i++;
	while (i < data->nb_total && (data->input[i].file.type == TRUNC || data->input[i].file.type == APPEND))
	{
		fdouts++;
		i++;
	}
	if (fdouts == 0)
	{
		data->fd_out = malloc(sizeof(int) * 2);
		data->fd_out[0] = STDOUT_FILENO;
		data->fd_out[1] = -1;
		return ;
	}
	data->fd_out = malloc(sizeof(int) * (fdouts + 1));
	i = i - fdouts;
	fdouts = 0;
	while (i < data->nb_total && (data->input[i].file.type == TRUNC || data->input[i].file.type == APPEND))
	{	
		data->fd_out[fdouts] = data->input[i].file.fd;
		i++;
		fdouts++;
	}
	data->fd_out[fdouts] = -1;
}
