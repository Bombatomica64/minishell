/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/30 14:54:09 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_inout(t_pipex *comm, t_input *input,
t_data *data, t_pipex **origin)
{
	if (input->type == INPUT)
	{
		if (comm->fd_in >= 0 && comm->fd_in != STDIN_FILENO)
			close(comm->fd_in);
		comm->fd_in = open_type(input->path, INPUT, data);
	}
	else if (input->type == HEREDOC)
	{
		if (comm->fd_in >= 0 && comm->fd_in != STDIN_FILENO)
			close(comm->fd_in);
		comm->fd_in = heredoc_creat(ft_strdup(input->node), data, comm, origin);
	}
	else if (input->type == TRUNC || input->type == APPEND)
	{
		if (comm->fd_out >= 0 && comm->fd_out != STDOUT_FILENO)
			close(comm->fd_out);
		comm->fd_out = open_type(input->path, input->type, data);
	}
	if (comm->fd_in == ERROR && input->type == HEREDOC)
		return (ERROR);
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
	if ((*data)->cmd_nbr == 0 && (*data)->in_pipe == FALSE)
	{
		pipe((*data)->fd[(*data)->cmd_nbr]);
		comm->fd_out = fd_io_check(comm->fd_out, STDOUT_FILENO,
				(*data)->fd[(*data)->cmd_nbr][1]);
		(*data)->in_pipe = TRUE;
	}
	else if ((*data)->cmd_nbr < (*data)->pipe_nbr - 1)
	{
		comm->fd_in = fd_io_check(comm->fd_in, STDIN_FILENO,
				(*data)->fd[(*data)->cmd_nbr][0]);
		pipe((*data)->fd[(*data)->cmd_nbr + 1]);
		comm->fd_out = fd_io_check(comm->fd_out, STDOUT_FILENO,
				(*data)->fd[(*data)->cmd_nbr + 1][1]);
		(*data)->cmd_nbr++;
	}
	else if ((*data)->cmd_nbr == (*data)->pipe_nbr - 1)
	{
		comm->fd_in = fd_io_check(comm->fd_in, STDIN_FILENO,
				(*data)->fd[(*data)->cmd_nbr][0]);
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
}

t_pipex	input_exec(t_data **data, t_pipex **origin)
{
	t_pipex	comm;
	t_bool	seen;

	seen = FALSE;
	comm = basic_set(data);
	while ((*data)->input && (*data)->input->type != FINISH)
	{
		if (set_inout(&comm, (*data)->input, *data, origin) == ERROR)
			return (free_matrix(&comm.cmd), comm_error(data));
		if (ft_iscmd((*data)->input, *data) == ERROR)
			return (comm_error(data));
		else if (ft_iscmd((*data)->input, *data) == TRUE)
			set_command(data, &comm, &seen);
		if ((*data)->input->type == PIPPE)
		{
			if (++(*data)->counter == 1)
				do_pipes(data, &comm);
			if (seen == TRUE)
				return (comm);
			do_pipes(data, &comm);
		}
		(*data)->input = (*data)->input->next;
	}
	return (comm);
}
