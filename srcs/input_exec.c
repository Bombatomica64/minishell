/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:22:43 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/19 18:01:20 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_inout(t_pipex *comm, t_input *input, t_data *data)
{
	if (input->type == INPUT)
	{
		if (comm->fd_in >= 0 && comm->fd_in != STDIN_FILENO)
			close(comm->fd_in);
		comm->fd_in = open_type(input->path, INPUT, data);
	}
	else if (input->type == HEREDOC)
		comm->fd_in = heredoc_creat(input->node, data, 0);
	else if (input->type == TRUNC || input->type == APPEND)
	{
		if (comm->fd_out >= 0 && comm->fd_out != STDOUT_FILENO)
			close(comm->fd_out);
		comm->fd_out = open_type(input->path, input->type, data);
	}
	if (comm->fd_in == -1 || comm->fd_out == -1)
		return (-1);
	return (0);
}

static t_pipex	basic_set(t_data **data)
{
	t_pipex	comm;

	dup2((*data)->original_stdin, STDIN_FILENO);
	dup2((*data)->original_stdout, STDOUT_FILENO);
	comm.fd_in = (STDIN_FILENO);
	comm.fd_out = (STDOUT_FILENO);
	comm.cmd = NULL;
	return (comm);
}

void	do_pipes(t_data **data, t_pipex *comm)
{
	if ((*data)->in_pipe == FALSE)
	{
		pipe((*data)->fd[(*data)->cmd_nbr]);
		if (comm->fd_out == STDOUT_FILENO)
			comm->fd_out = ((*data)->fd[0][1]);
		(*data)->in_pipe = TRUE;
	}
	else if ((*data)->cmd_nbr < (*data)->pipe_nbr - 1)
	{
		if (comm->fd_in == STDIN_FILENO)
			comm->fd_in = (*data)->fd[(*data)->cmd_nbr][0];
		pipe((*data)->fd[(*data)->cmd_nbr + 1]);
		if (comm->fd_out == STDOUT_FILENO)
			comm->fd_out = (*data)->fd[(*data)->cmd_nbr + 1][1];
		(*data)->cmd_nbr++;
	}
	else
	{
		if (comm->fd_in == STDIN_FILENO)
			comm->fd_in = (*data)->fd[(*data)->cmd_nbr][0];
		(*data)->in_pipe = FALSE;
		(*data)->cmd_nbr++;
	}
}

static void	set_command(t_data **data, t_pipex *comm, t_bool *seen)
{
	*seen = TRUE;
	if (!ft_strncmp((*data)->input->node, "cd ", 3))
		comm->cmd = ft_neosplitarg((*data)->input->node);
	else
		comm->cmd = ft_splitarg((*data)->input->node);
	comm->path = (*data)->input->path;
	if ((*data)->in_pipe == TRUE)
		do_pipes(data, comm);
}

t_pipex	input_exec(t_data **data)
{
	t_pipex	comm;
	t_bool	seen;

	comm = basic_set(data);
	seen = FALSE;
	while ((*data)->input && (*data)->input->type != FINISH)
	{
		if (set_inout(&comm, (*data)->input, *data) == -1)
			return (free_matrix(&comm.cmd), comm);
		if (ft_iscmd((*data)->input, *data) == TRUE)
		{
			if (seen == FALSE)
				set_command(data, &comm, &seen);
			else
			{
				if ((*data)->cmd_nbr == 0 && (*data)->pipe_nbr > 0)
					do_pipes(data, &comm);
				return (comm);
			}
		}
		(*data)->input = (*data)->input->next;
	}
	return (comm);
}
