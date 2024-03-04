/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:22:43 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/04 10:47:17 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_inout(t_pipex *comm, t_input *input)
{
	if (input->type == INPUT)
		comm->fd_in = open_type(input->path, INPUT);
	else if (input->type == HEREDOC)
		comm->fd_in = heredoc_creat(input->node);
	else if (input->type == TRUNC || input->type == APPEND)
		comm->fd_out = open_type(input->path, input->type);
}

static t_bool	ft_iscmd(t_input *input)
{
	if (!input)
		return (ERROR);
	if (input->type == COMMAND || input->type == BUILT_IN)
		return (TRUE);
	return (FALSE);
}

static t_pipex	basic_set(t_data **data)
{
	t_pipex	comm;

	comm.fd_in = dup(STDIN_FILENO);
	comm.fd_out = dup(STDOUT_FILENO);
	(void)data;
	return (comm);
}

void	do_pipes(t_data **data, t_pipex *comm)
{
	if ((*data)->in_pipe == FALSE)
	{
		pipe((*data)->fd[(*data)->last_pipe]);
		comm->fd_out = dup((*data)->fd[(*data)->last_pipe][1]);
		(*data)->in_pipe = TRUE;
	}
	else if ((*data)->in_pipe == TRUE
		&& (*data)->last_pipe <= (*data)->pipe_nbr - 1)
	{
		comm->fd_in = (*data)->fd[(*data)->last_pipe][0];
		pipe((*data)->fd[(*data)->last_pipe + 1]);
		comm->fd_out = (*data)->fd[(*data)->last_pipe + 1][1];
	}
	else
	{
		comm->fd_in = (*data)->fd[(*data)->last_pipe - 1][0];
		(*data)->in_pipe = FALSE;
	}
	(*data)->last_pipe++;
}

t_pipex	input_exec(t_data **data)
{
	t_pipex	comm;

	comm = basic_set(data);
	while ((*data)->input)
	{
		is_inout(&comm, (*data)->input);
		if (ft_iscmd((*data)->input) == TRUE)
		{
			comm.cmd = ft_splitarg((*data)->input->node);
			comm.path = (*data)->input->path;
			if (((*data)->input->next && ft_iscmd((*data)->input->next) == TRUE)
				|| (*data)->in_pipe == TRUE)
				do_pipes(data, &comm);
			if ((*data)->input->next != NULL)
				(*data)->input = (*data)->input->next;
			return (comm);
		}
		if ((*data)->input->next == NULL)
			return (comm);
		(*data)->input = (*data)->input->next;
	}
	return (comm);
}
