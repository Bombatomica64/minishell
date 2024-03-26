/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_inout.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:05:07 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/26 15:41:30 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_type(char *str, t_type type, t_data *data)
{
	int	fd;

	fd = -1;
	if (type == TRUNC)
		fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(str, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (type == INPUT)
	{
		if (check_access(str, type, data) != 0)
			return (-1);
		fd = open(str, O_RDONLY);
	}
	if (fd < 0)
		ft_error(str, OPEN, 101, data);
	return (fd);
}

void	close_fds(t_pipex *comm)
{
	if (comm->fd_in != STDIN_FILENO)
		close(comm->fd_in);
	if (comm->fd_out != STDOUT_FILENO)
		close(comm->fd_out);
}
