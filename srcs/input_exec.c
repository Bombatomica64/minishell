/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:22:43 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/28 16:42:02 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_inout(t_pipex **comm, t_input *input)
{
	if (input->type == INPUT)
	{
		(*comm)->filein = ft_strdup(input->node);
		(*comm)->fd_in = open_type(input->path, INPUT);
	}
	else if (input->type == HEREDOC)
	{
		(*comm)->filein = "heredoc";
		(*comm)->fd_in = heredoc_creat(input->node);
	}
	else if (input->type == TRUNC || input->type == APPEND)
	{
		(*comm)->fileout = ft_strdup(input->node);
		(*comm)->fd_out = open_type(input->path, input->type);
	}
}

static t_bool	ft_iscmd(t_input *input)
{
	if (!input)
		return (ERROR);
	if (input->type == COMMAND || input->type == BUILT_IN)
		return (TRUE);
	return (FALSE);
}

static t_pipex	*basic_set(t_data **data)
{
	t_pipex	*comm;

	comm = malloc(sizeof(t_pipex));
	if (!comm)
		return (NULL);
	comm->fd_in = dup((*data)->fd[0]);
	comm->fd_out = STDOUT_FILENO;
	return (comm);
}

t_pipex	*input_exec(t_data **data)
{
	t_pipex	*comm;

	comm = basic_set(data);
	while ((*data)->input)
	{
		is_inout(&comm, (*data)->input);
		if (ft_iscmd((*data)->input) == TRUE)
		{
			comm->cmd = ft_splitarg((*data)->input->node);
			comm->path = (*data)->input->path;
			if ((*data)->input->next && ft_iscmd((*data)->input->next) == TRUE)
			{
				if (pipe((*data)->fd) == -1)
					ft_error("input_exec", PIPE, 132, (*data));
				comm->fd_out = dup((*data)->fd[1]);
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
