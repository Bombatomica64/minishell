/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:22:43 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/27 11:49:04 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_input(char **name, int *fd, t_input *input)
{
	if (input->type == INPUT)
	{
		*name = input->node;
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

static t_bool	ft_iscmd(t_input *input)
{
	if (!input)
		return (ERROR);
	if (input->type == COMMAND || input->type == BUILT_IN)
		return (TRUE);
	return (FALSE);
}

static t_pipex *basic_set(t_data **data)
{
	t_pipex	*comm;

	comm = malloc(sizeof(t_pipex));
	if (!comm)
		return (NULL);
	comm->fd_in = (*data)->fd[0];
	comm->fd_out = (*data)->fd[1];
	return (comm);
}

t_pipex	*input_exec(t_data **data)
{
	t_pipex	*comm;

	comm = basic_set(data);
	while ((*data)->input)
	{
		is_input(&comm->filein, &comm->fd_in, (*data)->input);
		is_output(&comm->fileout, &comm->fd_out, (*data)->input);
		if (ft_iscmd((*data)->input) == TRUE)
		{
			comm->cmd = ft_splitarg((*data)->input->node);
			comm->path = (*data)->input->path;
			if ((*data)->input->next && ft_iscmd((*data)->input->next) == TRUE)
			{
				if (pipe((*data)->fd) == -1)
					ft_error("input_exec", PIPE, 132, (*data));
				comm->fd_out = (*data)->fd[1];
				printf("pipe usata\n%s\n", (*data)->input->node);
			}
			(*data)->input = (*data)->input->next;
			return (comm);
		}
		(*data)->input = (*data)->input->next;
	}
	return (comm);
}
