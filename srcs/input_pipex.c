/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 23:05:54 by marvin            #+#    #+#             */
/*   Updated: 2024/02/19 11:40:30 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_for_pipex(t_data *data)
{
	//data->in_p.fds = malloc(sizeof(int) * (data->nb_cmds * 2));
	/*if (data->in_p.fds == NULL)
		ft_error("malloc", MALLOC_ERROR);*/
	data->in_p.fds[0] = data->fd_in;
	data->in_p.fds[1] = data->fd_out;
}

void	malloc_input_pipex(t_data *data, int i)
{
	data->input_found = FALSE;
	data->nb_cmds = 0;
	data->nb_files = 0;
	while (i < data->nb_total)
	{
		if (data->input[i].is_a_file == TRUE)
		{
			data->nb_files++;
			if (data->input[i].file.type == INPUT)
				data->input_found = TRUE;
		}
		else
			data->nb_cmds++;
		i++;
	}
	if (data->input_found == FALSE)
		data->nb_files++;
	data->in_p.cmds = malloc(sizeof(char *) * (data->nb_cmds + 1));
	/*if (data->in_p.cmds == NULL)
		ft_error("malloc", MALLOC_ERROR);*/
	data->in_p.files = malloc(sizeof(char *) * (data->nb_files + 1));
	/*if (data->in_p.files == NULL)
		ft_error("malloc", MALLOC_ERROR);*/
}

void	input_for_pipex(t_data *data, int i)
{
	malloc_input_pipex(data, i);
	data->nb_cmds = 0;
	data->nb_files = 0;
	if (data->input_found == FALSE)
	{
		data->in_p.files[data->nb_files] = NULL;
		data->nb_files++;
	}
	while (i < data->nb_total)
	{
		if (data->input[i].is_a_file == TRUE)
		{
			data->in_p.files[data->nb_files] = data->input[i].file.name;
			data->nb_files++;
		}
		else
		{
			data->in_p.cmds[data->nb_cmds] = data->input[i].cmd.name;
			data->nb_cmds++;
		}
		i++;
	}
	data->in_p.cmds[data->nb_cmds] = NULL;
	data->in_p.files[data->nb_files] = NULL;
	fd_for_pipex(data);
}
