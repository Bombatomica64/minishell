/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_inout.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:05:07 by marvin            #+#    #+#             */
/*   Updated: 2024/02/21 18:15:28 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_type(char *str, t_type type)
{
	int	fd;

	fd = 0;
	if (type == TRUNC)
		fd = open(str, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	else if (type == APPEND)
		fd = open(str, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	else if (type == INPUT)
		fd = open(str, O_RDONLY);
	else if (type == HEREDOC)
		heredoc_creat(str);
	if (fd < 0)
		ft_error("open_type", OPEN, 101, NULL);
	return (fd);
}

int	fd_in(t_data data)
{
	while (data.input != NULL && (data.input->type != INPUT
			|| data.input->type != HEREDOC))
		data.input = data.input->next;
	while (data.input != NULL && (data.input->type == INPUT
			|| data.input->type == HEREDOC))
	{
		if (data.input->type == INPUT && data.input->next->type != INPUT
			&& data.input->next->type != HEREDOC)
			return (open_type(data.input->node, INPUT));
		if (data.input->type == HEREDOC)
			heredoc_creat(data.input->node);
		if (data.input->next->type != INPUT
			&& data.input->next->type != HEREDOC)
			return (open_type(".heredoc.txt", INPUT));
		data.input = data.input->next;
	}
	return (STDIN_FILENO);
}

int	fd_out(t_data data)
{
	while (data.input != NULL && (data.input->type != TRUNC
			|| data.input->type != APPEND))
		data.input = data.input->next;
	while (data.input != NULL && (data.input->type == TRUNC
			|| data.input->type == APPEND))
	{
		if (data.input->type == TRUNC && data.input->next->type != TRUNC
			&& data.input->next->type != APPEND)
			return (open_type(data.input->node, TRUNC));
		if (data.input->type == APPEND && data.input->next->type != TRUNC
			&& data.input->next->type != APPEND)
			return (open_type(data.input->node, APPEND));
		data.input = data.input->next;
	}
	return (STDOUT_FILENO);
}
