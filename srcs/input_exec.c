/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:22:43 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/26 16:41:06 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_input(char **name, int *fd, t_input *input)
{
	if (input->type == INPUT)
	{
		*name = data->input->node;
		*fd = open_type(input->path, INPUT);
	}
	else if (input->type == HEREDOC)
	{
		*name = "heredoc";
		*fd = heredoc_creat(input->node);
	}
}

static void	is_output(char **name, int *fd, t_input *input)
{
	if (input->type == TRUNC || input->type == APPEND)
	{
		*name = input->node;
		*fd = open_type(input->path, input->type);
	}
}

t_pipex	input_exec(t_data *data)
{
	t_pipex	comm;

	comm.fd_in = data->fd[0];
	comm.fd_out = data->fd[1];
	while (data->input)
	{
		is_input(&comm.filein, &comm.fd_in, data->input);
		is_output(&comm.fileout, &comm.fd_out, data->input);
		if (data->input->type == COMMAND || data->input->type == BUILT_IN)
		{
			comm.cmd = ft_splitarg(data->input->node);
			comm.path = data->input->path;
			if (data->input->next && (data->input->next->type == COMMAND
					|| data->input->next->type == BUILT_IN))
			{
				if (pipe(data->fd) == -1)
					ft_error("input_exec", PIPE, 132, data);
				comm.fd_out = data->fd[1];
			}
			return (comm);
		}
		data->input = data->input->next;
	}
	return (comm);
}
