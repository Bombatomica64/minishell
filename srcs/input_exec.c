/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:22:43 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/12 12:38:57 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_inout(t_pipex *comm, t_input *input, t_data *data)
{
	if (input->type == INPUT)
		comm->fd_in = open_type(input->path, INPUT);
	else if (input->type == HEREDOC)
		comm->fd_in = heredoc_creat(input->node, data);
	else if (input->type == TRUNC || input->type == APPEND)
		comm->fd_out = open_type(input->path, input->type);
}

static t_pipex	basic_set(t_data **data)
{
	t_pipex	comm;

	dup2((*data)->original_stdin, STDIN_FILENO);
	dup2((*data)->original_stdout, STDOUT_FILENO);
	comm.fd_in = (STDIN_FILENO);
	printf("comm.fd_in: %d\n", comm.fd_in);
	comm.fd_out = (STDOUT_FILENO);
	return (comm);
}

void	do_pipes(t_data **data, t_pipex *comm)
{
	if ((*data)->in_pipe == FALSE)
	{
		pipe((*data)->fd[(*data)->cmd_nbr]);
		comm->fd_out = ((*data)->fd[0][1]);
		(*data)->in_pipe = TRUE;
	}
	else if ((*data)->cmd_nbr < (*data)->pipe_nbr - 1)
	{
		comm->fd_in = (*data)->fd[(*data)->cmd_nbr][0];
		pipe((*data)->fd[(*data)->cmd_nbr + 1]);
		comm->fd_out = (*data)->fd[(*data)->cmd_nbr + 1][1];
		(*data)->cmd_nbr++;
	}
	else
	{
		fprintf(stderr,"cmd nbr:%d\n", (*data)->cmd_nbr);
		for (int i = 0; i < (*data)->pipe_nbr; i++)
		{
			for (int j = 0; j < 2; j++)
				printf ("fd[%d][%d]: %d\n", i, j, (*data)->fd[i][j]);
		}
		comm->fd_in = (*data)->fd[(*data)->cmd_nbr][0];
		(*data)->in_pipe = FALSE;
		(*data)->cmd_nbr++;
	}
}

t_pipex	input_exec(t_data **data)
{
	t_pipex	comm;
	t_bool	seen;

	comm = basic_set(data);
	seen = FALSE;
	while ((*data)->input && (*data)->input->type != FINISH)
	{
		set_inout(&comm, (*data)->input, *data);
		if (ft_iscmd((*data)->input) == TRUE)
		{
			if (seen == FALSE)
			{
				seen = TRUE;
				comm.cmd = ft_splitarg((*data)->input->node);
				comm.path = (*data)->input->path;
				if ((*data)->in_pipe == TRUE)
					do_pipes(data, &comm);
			}
			else
			{
				if ((*data)->cmd_nbr == 0)
					do_pipes(data, &comm);
				return (comm);
			}
		}
		(*data)->input = (*data)->input->next;
	}
	return (comm);
}
