/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:22:43 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/01 16:09:21 by gduranti         ###   ########.fr       */
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

	comm.fd_in = dup((*data)->fd[0]);
	comm.fd_out = dup((*data)->original_stdout);
	return (comm);
}

t_pipex	input_exec(t_data **data)
{
	t_pipex	comm;

	printf("ciao bro\n");
	comm = basic_set(data);
	while ((*data)->input)
	{
		is_inout(&comm, (*data)->input);
		if (ft_iscmd((*data)->input) == TRUE)
		{
			comm.cmd = ft_splitarg((*data)->input->node);
			comm.path = (*data)->input->path;
			if ((*data)->input->next && ft_iscmd((*data)->input->next) == TRUE)
			{
				if (pipe((*data)->fd) == -1)
					ft_error("input_exec", PIPE, 132, (*data));
				comm.fd_out = dup((*data)->fd[1]);
			}
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
